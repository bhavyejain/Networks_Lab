BEGIN{ c=0;}
{
	if($1 == "d")
	{
		c++;
	}
}
END{printf("The number of packets dropped = %d\n",c);}