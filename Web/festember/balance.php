<?php
$con=mysqli_connect("localhost","festember","fest","festember");
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
$RollNo = mysqli_real_escape_string($con, $_POST['RollNo']);
$bal=mysqli_query($con,"SELECT balance FROM rfrollno where RollNo='$RollNo'");
$r=mysqli_fetch_array($bal);
if($r)
echo "Your Balance is Rs.".$r['balance'];
else
echo "Invalid RollNo";
?>