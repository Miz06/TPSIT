<?php
session_start();
require '../../references/connectionToDB/DBconn.php';

$config = require '../../references/connectionToDB/databaseConfig.php';

if (!isset($_SESSION['email']) || !isset($_POST['title']) || !isset($_POST['edition_year'])) {
    echo json_encode(['success' => false, 'message' => 'Dati mancanti']);
    exit;
}

$email = $_SESSION['email'];
$title = $_POST['title'];
$edition_year = $_POST['edition_year'];

$db = DBconn::getDB($config);

$query = "DELETE FROM save WHERE email = :email AND title = :title AND edition_year = :edition_year";
$stmt = $db->prepare($query);
$stmt->bindParam(':email', $email);
$stmt->bindParam(':title', $title);
$stmt->bindParam(':edition_year', $edition_year);

if ($stmt->execute()) {
    echo json_encode(['success' => true]);
} else {
    echo json_encode(['success' => false, 'message' => 'Errore nella rimozione']);
}
