<?php
session_start();
require '../../references/connectionToDB/DBconn.php';

$config = require '../../references/connectionToDB/databaseConfig.php';

// Legge il corpo della richiesta JSON
$data = json_decode(file_get_contents("php://input"), true);

// Verifica che i dati richiesti siano presenti
if (!isset($_SESSION['email']) || !isset($data['title']) || !isset($data['edition'])) {
    echo json_encode(['success' => false, 'message' => 'Dati mancanti']);
    exit;
}

$email = $_SESSION['email'];
$title = $data['title'];
$edition_year = $data['edition'];

try {
    $db = DBconn::getDB($config);

    // Query di eliminazione
    $query = "DELETE FROM save WHERE email = :email AND title = :title AND edition_year = :edition_year";
    $stmt = $db->prepare($query);
    $stmt->bindParam(':email', $email);
    $stmt->bindParam(':title', $title);
    $stmt->bindParam(':edition_year', $edition_year);

    if ($stmt->execute()) {
        echo json_encode(['success' => true, 'message' => 'Elemento rimosso con successo']);
    } else {
        echo json_encode(['success' => false, 'message' => 'Errore nella rimozione']);
    }
} catch (Exception $e) {
    echo json_encode(['success' => false, 'message' => 'Errore del server: ' . $e->getMessage()]);
}
?>
