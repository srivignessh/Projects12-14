<?php
$con=mysqli_connect("localhost","festember","fest","festember");
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
$StallNo = mysqli_real_escape_string($con, $_POST['StallNo']);
$bill=mysqli_query($con,"SELECT COUNT(*) as total FROM $StallNo");
$r=mysqli_fetch_array($bill);
echo $r['total'];
?>
