#Create a simulator object
set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

$ns rtproto DV

#Open the nam trace file
set nf [open out.nam w]
set tracefd [open traceout2.tr w]
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

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$ns duplex-link $n0 $n2 1.5Mb 5ms DropTail
$ns duplex-link $n1 $n2 1.5Mb 5ms DropTail
$ns duplex-link $n2 $n3 1Mb 5ms DropTail
$ns duplex-link $n3 $n4 1.5Mb 5ms DropTail
$ns duplex-link $n3 $n5 1.5Mb 5ms DropTail

$ns duplex-link-op $n2 $n0 orient left-up
$ns duplex-link-op $n2 $n1 orient left-down
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right-up
$ns duplex-link-op $n3 $n5 orient right-down

$ns queue-limit $n2 $n3 15
$ns duplex-link-op $n2 $n3 queuePos 0.5

$ns queue-limit $n3 $n2 15
$ns duplex-link-op $n3 $n2 queuePos 0.5

$ns queue-limit $n0 $n2 15
$ns duplex-link-op $n0 $n2 queuePos 0.5

$ns queue-limit $n3 $n4 15
$ns duplex-link-op $n3 $n4 queuePos 0.5

$ns queue-limit $n5 $n3 15
$ns duplex-link-op $n5 $n3 queuePos 0.5

$ns queue-limit $n2 $n0 15
$ns duplex-link-op $n2 $n0 queuePos 0.5

#Create a TCP agent and attach it to node n0
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
#Create a TCP Sink agent (a traffic sink) for TCP and attach it to node n2
set sink0 [new Agent/TCPSink]
$ns attach-agent $n4 $sink0
#Connect the traffic sources with the traffic sink
$ns connect $tcp0 $sink0

#Create a TCP agent and attach it to node n5
set tcp1 [new Agent/TCP]
$ns attach-agent $n5 $tcp1
#Create a TCP Sink agent (a traffic sink) for TCP and attach it to node n1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
#Connect the traffic sources with the traffic sink
$ns connect $tcp1 $sink1

$tcp0 set fid_ 1
$tcp1 set fid_ 2

# Create a CBR traffic source and attach it to tcp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $tcp0

# Create a FTP and attach it to tcp1
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp1

#Schedule events for the CBR agents
$ns at 0.1 "$cbr0 start"
$ns at 0.2 "$ftp0 start"

$ns at 4.0 "$ftp0 stop"
$ns at 4.5 "$cbr0 stop"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run