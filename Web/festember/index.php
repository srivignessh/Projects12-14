 <?php
$con=mysqli_connect("localhost","festember","fest","festember");
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

// escape variables for security
$RfidNo = mysqli_real_escape_string($con, $_POST['RfidNo']);
$StallNo = mysqli_real_escape_string($con, $_POST['StallNo']);
$Pass = mysqli_real_escape_string($con, $_POST['Pass']);
$Amount = mysqli_real_escape_string($con, $_POST['Amount']);
$BillNo = mysqli_real_escape_string($con, $_POST['BillNo']);
$MOP = mysqli_real_escape_string($con, $_POST['MOP']);
$MOP1='CARD';
$MOP2='CASH';
$u=1;
//echo $RfidNo.$StallNo.$Amount.$Pass.$BillNo.$MOP;
if($Amount)
{
if($RfidNo)
{	
$table=mysqli_query($con,"SELECT PASS FROM food_stall WHERE STALLNO='$StallNo'");
while($stall = mysqli_fetch_array($table)) 
	{
		if($stall['PASS']=$Pass)
		{   $roll=mysqli_query($con,"SELECT rollno,balance FROM rfrollno where RFIDNo='$RfidNo'");

			while($stno = mysqli_fetch_array($roll)) 
				{	
					$u=0;
					$stid=$stno['rollno'];
					$stbl=$stno['balance'];
					#echo $stid;
					#echo $stbl;
					if($MOP==$MOP1)
						{
						if($stbl>=$Amount)
						{
							#echo $MOP1;
							$newbl=$stbl-$Amount;
							#echo $newbl;
							#echo $StallNo;

							$updte=mysqli_query($con,"UPDATE rfrollno SET Balance = '$newbl' WHERE RollNo = '$stid'");
							$rept=mysqli_query($con,"INSERT INTO $StallNo (billno, rollno, amount) VALUES ('$BillNo', '$stid', '$Amount')");
							echo "Transaction SuccessFull";
						}
						elseif($stbl)
						{
							echo "Insuffient Balance";
						}
						else
						{
							echo "Sorry CARD No Balance";
						}
						}
					elseif ($MOP==$MOP2) 
						{
						#echo $MOP2;
						$rept=mysqli_query($con,"INSERT INTO $StallNo (billno, rollno, amount) VALUES ('$BillNo', '$stid', '$Amount')");
						#echo $stbl;
						echo "Transaction SuccessFull";
						# code...
						}
					else
					{
						echo "Wrong mode of Payment";
					}

			
			
				}
			if($u)
			{
				echo "Enter Valid RFID No";
			}		
		}
		else
		{ 
			echo "Wrong Password";

		}


	}
}
else
{
	echo "Enter RFidNo";
}
}
else
{
    echo "Enter Amount";
}

?>