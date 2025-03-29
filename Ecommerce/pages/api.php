<?php
$servername = "localhost";
$username = "root"; // Cambia se necessario
$password = ""; // Cambia se necessario
$dbname = "DB_GameShop";

// Connessione al database
$conn = new mysqli($servername, $username, $password, $dbname);

// Controllo connessione
if ($conn->connect_error) {
    die("Connessione fallita: " . $conn->connect_error);
}

// Query per selezionare i dati dalla tabella games con le edizioni
$sql = "SELECT g.title, g.type, g.text, g.image, g.price, 
               GROUP_CONCAT(h.edition_year ORDER BY h.edition_year ASC) AS editions
        FROM games g 
        LEFT JOIN `having` h ON g.title = h.title
        GROUP BY g.title";


$result = $conn->query($sql);

$games = [];

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $games[] = [
            "title" => $row["title"],
            "text" => $row["text"],
            "type" => $row["type"],
            "image" => $row["image"],
            "price" => ($row["price"] > 0) ? "€" . number_format($row["price"], 2) : "Gratis (con acquisti in-game)",
            "editions" => explode(",", $row["editions"]) // Converti in array
        ];
    }
}

// Creazione del file JSON
$data = ["games" => $games];
$json = json_encode($data, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES);
file_put_contents("./archivio/archivio.json", $json);

echo "File JSON creato con successo.";

// Chiudi connessione
$conn->close();
?>
