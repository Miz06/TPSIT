<?php
session_start();

// Funzione per scrivere gli errori su un file
function logErrorToFile($message) {
    $logFile = __DIR__ . '/error_log.txt';
    file_put_contents($logFile, date('Y-m-d H:i:s') . " - " . $message . PHP_EOL, FILE_APPEND);
}

require '../../references/connectionToDB/DBconn.php';
$config = require '../../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

// Verifica che il metodo sia POST
if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    echo json_encode(['success' => false, 'error' => 'Metodo non consentito']);
    exit;
}

// Decodifica il JSON ricevuto
$input = json_decode(file_get_contents('php://input'), true);
logErrorToFile("Dati ricevuti: " . print_r($input, true));

if (!isset($input['title'], $input['edition'], $input['quantity'])) {
    http_response_code(400);
    echo json_encode(['success' => false, 'error' => 'Dati mancanti']);
    exit;
}

$title = trim($input['title']);
$edition = trim($input['edition']);
$quantity = filter_var($input['quantity'], FILTER_VALIDATE_INT);

if ($quantity === false || $quantity <= 0) {
    http_response_code(400);
    echo json_encode(['success' => false, 'error' => 'Quantità non valida']);
    exit;
}

if (!isset($_SESSION['email'])) {
    logErrorToFile("Errore: sessione email non impostata!");
    http_response_code(401);
    echo json_encode(['success' => false, 'error' => 'Utente non autenticato']);
    exit;
}

$user_email = $_SESSION['email'];
logErrorToFile("Email utente: " . $user_email);


try {
    // Utilizza la connessione già aperta
    $pdo = $db;

    logErrorToFile("Dati da inserire: Title: $title, Edition: $edition, Quantity: $quantity");

    $stmt = $pdo->prepare("INSERT INTO buy (quantity, customer_email, game_title, edition_year) 
                        VALUES (:quantity, :customer_email, :title, :edition)");
    $stmt->bindParam(':quantity', $quantity, PDO::PARAM_INT);
    $stmt->bindParam(':customer_email', $user_email);
    $stmt->bindParam(':title', $title);
    $stmt->bindParam(':edition', $edition);

    if ($stmt->execute()) {
        // Rimuove l'elemento dalla tabella save
        $deleteStmt = $pdo->prepare("DELETE FROM save WHERE title = :title AND edition_year = :edition AND email = :customer_email");
        $deleteStmt->bindParam(':title', $title);
        $deleteStmt->bindParam(':edition', $edition);
        $deleteStmt->bindParam(':customer_email', $user_email);

        if ($deleteStmt->execute()) {
            echo json_encode(['success' => true]);
        } else {
            logErrorToFile("Errore nella rimozione dal carrello: " . implode(", ", $deleteStmt->errorInfo()));
            http_response_code(500);
            echo json_encode(['success' => false, 'error' => 'Errore nella rimozione dal carrello']);
        }
    } else {
        logErrorToFile("Errore nell'inserimento nel database: " . implode(", ", $stmt->errorInfo()));
        http_response_code(500);
        echo json_encode(['success' => false, 'error' => 'Errore nell\'inserimento nel database']);
    }

} catch (PDOException $e) {
    http_response_code(500);
    echo json_encode(['success' => false, 'error' => $e->getMessage()]);
}