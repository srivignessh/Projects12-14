<?php

$con=mysqli_connect("localhost","festember","fest","festember");
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

// escape variables for security
$value=mysqli_real_escape_string($con, $_POST['v']);
$result = mysqli_query($con,"SELECT * FROM rfrollno where No='$value'");
echo "<table border='1'>
<tr>
<th>No</th>
<th>RFIDNo</th>
<th>RollNo</th>
</tr>";

while($row = mysqli_fetch_array($result)) {
  echo "<tr>";
  echo "<td>" . $row['No'] . "</td>";
  echo "<td>" . $row['RFIDNo'] . "</td>";
  echo "<td>" . $row['RollNo'] . "</td>";
  echo "</tr>";
}

echo "</table>";
mysqli_close($con);

?>