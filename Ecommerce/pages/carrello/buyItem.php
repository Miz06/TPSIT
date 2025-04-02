<?php
session_start();
require '../../references/connectionToDB/DBconn.php';
$config = require '../../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    echo json_encode(['success' => false, 'error' => 'Metodo non consentito']);
    exit;
}

$input = json_decode(file_get_contents('php://input'), true);
if (!isset($input['items']) || !is_array($input['items'])) {
    http_response_code(400);
    echo json_encode(['success' => false, 'error' => 'Dati mancanti']);
    exit;
}

if (!isset($_SESSION['email'])) {
    http_response_code(401);
    echo json_encode(['success' => false, 'error' => 'Utente non autenticato']);
    exit;
}

$user_email = $_SESSION['email'];
$pdo = $db;

try {
    $pdo->beginTransaction();

    // Imposta la data corrente
    $date = date('Y-m-d');

    // Per garantire timestamp unici, aggiungiamo un incremento in secondi
    $baseTime = strtotime(date('H:i:s'));

    foreach ($input['items'] as $index => $item) {
        $title = trim($item['title']);
        $edition = trim($item['edition']);
        $quantity = filter_var($item['quantity'], FILTER_VALIDATE_INT);

        if ($quantity === false || $quantity <= 0) {
            throw new Exception('Quantità non valida per il prodotto: ' . $title);
        }

        // Calcola un orario unico incrementando di $index secondi
        $uniqueTime = date('H:i:s', $baseTime + $index);

        // Inserisce l'acquisto nella tabella "buy"
        $stmt = $pdo->prepare("INSERT INTO buy (quantity, customer_email, game_title, edition_year, date, time) 
                              VALUES (:quantity, :customer_email, :title, :edition, :date, :time)");
        $stmt->bindParam(':quantity', $quantity, PDO::PARAM_INT);
        $stmt->bindParam(':customer_email', $user_email);
        $stmt->bindParam(':title', $title);
        $stmt->bindParam(':edition', $edition);
        $stmt->bindParam(':date', $date);
        $stmt->bindParam(':time', $uniqueTime);
        $stmt->execute();

        // Rimuove il prodotto dalla tabella "save"
        $deleteStmt = $pdo->prepare("DELETE FROM save WHERE title = :title AND edition_year = :edition AND email = :customer_email");
        $deleteStmt->bindParam(':title', $title);
        $deleteStmt->bindParam(':edition', $edition);
        $deleteStmt->bindParam(':customer_email', $user_email);
        $deleteStmt->execute();
    }

    $pdo->commit();
    echo json_encode(['success' => true]);
} catch (Exception $e) {
    $pdo->rollBack();
    http_response_code(500);
    echo json_encode(['success' => false, 'error' => $e->getMessage()]);
}
