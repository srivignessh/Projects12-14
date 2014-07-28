 <?php
$con=mysqli_connect("localhost","festember","fest","my_db");
// Check connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

// escape variables for security
$firstname = mysqli_real_escape_string($con, $_POST['firstname']);
$lastname = mysqli_real_escape_string($con, $_POST['lastname']);
$age = mysqli_real_escape_string($con, $_POST['age']);

$sql="INSERT INTO Persons (FirstName, LastName, Age)
VALUES ('$firstname', '$lastname', '$age')";

if (!mysqli_query($con,$sql)) {
  die('Error: ' . mysqli_error($con));
}

echo "1 record added";
$result = mysqli_query($con,"SELECT * FROM Persons");
echo "<table border='1'>
<tr>
<th>Firstname</th>
<th>Lastname</th>
<th>Age</th>
</tr>";

while($row = mysqli_fetch_array($result)) {
  echo "<tr>";
  echo "<td>" . $row['FirstName'] . "</td>";
  echo "<td>" . $row['LastName'] . "</td>";
  echo "<td>" . $row['Age'] . "</td>";
  echo "</tr>";
}

echo "</table>";
mysqli_close($con);

?>