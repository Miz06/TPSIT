<?php
session_start();
require '../../references/connectionToDB/DBconn.php';

$config = require '../../references/connectionToDB/databaseConfig.php';

if (!isset($_SESSION['email'])) {
    echo json_encode([]);
    exit;
}

$email = $_SESSION['email'];
$db = DBconn::getDB($config);

$query = "SELECT s.title, s.edition_year, s.quantity, g.image, g.price 
          FROM save s
          JOIN games g ON s.title = g.title
          WHERE s.email = :email";

$stmt = $db->prepare($query);
$stmt->bindParam(':email', $email);
$stmt->execute();
$cartItems = $stmt->fetchAll(PDO::FETCH_ASSOC);

echo json_encode($cartItems);
?>
