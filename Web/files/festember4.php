<?php
$con=mysqli_connect("localhost","festember","fest");
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM students");

while($row = mysqli_fetch_array($result)) {
  echo $row['Name'] . " " . $row['Age'];
  echo "<br>";
}

mysqli_close($con);
?>