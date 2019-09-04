#Create a simulator object
set ns [new Simulator]

$ns color 1 Blue

$ns rtproto DV

#Open the nam trace file
set nf [open out.nam w]
set tracefd [open traceout1.tr w]
$ns namtrace-all $nf
$ns trace-all $tracefd

#Define a 'finish' procedure
proc finish {} {
    global ns nf
    $ns flush-trace
    #Close the trace file
    close $nf
    #Executenam on the trace file
    exec nam out.nam &
    exit0
}

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n1 $n2 1.5Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail

$ns queue-limit $n1 $n2 5
$ns duplex-link-op $n1 $n2 queuePos 0.5

$ns queue-limit $n2 $n3 5
$ns duplex-link-op $n2 $n3 queuePos 0.5

#Create a TCP agent and attach it to node n1
set tcp0 [new Agent/TCP]
$ns attach-agent $n1 $tcp0
#Create a TCP Sink agent (a traffic sink) for TCP and attach it to node n3
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
#Connect the traffic sources with the traffic sink
$ns connect $tcp0 $sink0

$tcp0 set fid_ 1

# Create a CBR traffic source and attach it to tcp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $tcp0

#Schedule events for the CBR agents
$ns at 0.5 "$cbr0 start"

$ns at 4.5 "$cbr0 stop"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run