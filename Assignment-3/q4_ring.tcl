set data [gets stdin]
scan $data "%d %d" N k

set ns  [new Simulator]

$ns color 0 Red
$ns color 1 Blue
$ns color 2 Yellow
$ns color 3 Green
$ns color 4 Orange
$ns color 5 Black

$ns rtproto DV

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam
    exit 0
}

for {set i 0} {$i < $N} {incr i} {
	set n($i) [$ns node]
}

for {set i 0} {$i < $N} {incr i} {
	$ns duplex-link $n($i) $n([expr ($i + 1) % $N]) 1Mb 10ms DropTail
}

for {set i 0} {$i < $k} {incr i} {
	set input [gets stdin]
	scan $input "%d %d" u v
	set tcp [new Agent/TCP]
	$ns attach-agent $n($u) $tcp
	$tcp set class_ $i
	$tcp set fid_ $i
	set sink [new Agent/TCPSink]
	$ns attach-agent $n($v) $sink
	$ns connect $tcp $sink
	set ftp0 [new Application/FTP]
	$ftp0 attach-agent $tcp
	$ns at 0.1 "$ftp0 start"
	$ns at 1.5 "$ftp0 stop"
}

$ns at 2.0 "finish"
$ns run