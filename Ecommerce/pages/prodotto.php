<?php
ob_start();
$title = 'prodotto';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    header('Content-Type: application/json');

    if (!isset($_SESSION['email'])) {
        echo json_encode(["success" => false, "message" => "Utente non autenticato"]);
        exit;
    }

    $email = $_SESSION['email'];

    // Controllo se i dati arrivano in JSON o tramite form POST
    $data = json_decode(file_get_contents("php://input"), true);

    if ($data) {
        $title = $data['title'] ?? null;
        $editionYear = $data['edition_year'] ?? null;
        $quantity = $data['quantity'] ?? 1; // Aggiungi la quantità
    } else {
        $title = $_POST['title'] ?? null;
        $editionYear = $_POST['edition_year'] ?? null;
        $quantity = $_POST['quantity'] ?? 1; // Aggiungi la quantità
    }

    // Controllo se i dati sono validi
    if (!$title || !$editionYear || !$quantity || $quantity < 1) {
        echo json_encode(["success" => false, "message" => "Dati mancanti o quantità non valida"]);
        exit;
    }

    try {
        // Verifica se il prodotto è già presente per l'utente e aggiorna la quantità
        $queryCheck = "SELECT quantity FROM DB_GameShop.save WHERE title = :title AND edition_year = :edition_year AND email = :email";
        $stmtCheck = $db->prepare($queryCheck);
        $stmtCheck->bindParam(':title', $title);
        $stmtCheck->bindParam(':edition_year', $editionYear);
        $stmtCheck->bindParam(':email', $email);
        $stmtCheck->execute();
        $existingProduct = $stmtCheck->fetch(PDO::FETCH_ASSOC);

        if ($existingProduct) {
            // Se il prodotto esiste, aggiorna la quantità
            $newQuantity = $existingProduct['quantity'] + $quantity;
            $queryUpdate = "UPDATE DB_GameShop.save SET quantity = :quantity WHERE title = :title AND edition_year = :edition_year AND email = :email";
            $stmtUpdate = $db->prepare($queryUpdate);
            $stmtUpdate->bindParam(':quantity', $newQuantity);
            $stmtUpdate->bindParam(':title', $title);
            $stmtUpdate->bindParam(':edition_year', $editionYear);
            $stmtUpdate->bindParam(':email', $email);
            $stmtUpdate->execute();
        } else {
            // Se il prodotto non esiste, lo inserisce nel database
            $queryInsert = "INSERT INTO DB_GameShop.save (title, edition_year, email, quantity) VALUES (:title, :edition_year, :email, :quantity)";
            $stmtInsert = $db->prepare($queryInsert);
            $stmtInsert->bindParam(':title', $title);
            $stmtInsert->bindParam(':edition_year', $editionYear);
            $stmtInsert->bindParam(':email', $email);
            $stmtInsert->bindParam(':quantity', $quantity);
            $stmtInsert->execute();
        }

        echo json_encode(["success" => true, "message" => "Prodotto salvato con quantità"]);
        exit;
    } catch (PDOException $e) {
        echo json_encode(["success" => false, "message" => "Errore: " . $e->getMessage()]);
        exit;
    }
}

ob_end_flush();
?>
<style>
    .container {
        margin-top: 3%;
    }

    .card {
        margin: 20px 0;
    }

    .card-img {
        width: 100%;
        object-fit: cover;
        margin-bottom: 10px;
    }

    /* Nascondi la freccia di incremento/decremento del campo number */
    input[type="number"]::-webkit-outer-spin-button,
    input[type="number"]::-webkit-inner-spin-button {
        -webkit-appearance: none;
        margin: 0;
    }

    .input-group {
        width: auto;
        border: 2px solid #007bff;
        border-radius: 10px;
        overflow: hidden;
    }

    .input-group .form-control {
        width: 40px;
        padding: 5px;
        font-size: 14px;
        text-align: center;
        border: none;
    }

    .input-group button {
        width: 30px;
        font-size: 14px;
        background-color: #007bff;
        color: white;
        border: none;
    }

    .input-group button:hover {
        background-color: #0056b3;
    }

    /* Stile per il prezzo */
    #game-price {
        border: 2px solid green;
        padding: 5px;
        border-radius: 10px;
        display: inline-block;
        white-space: nowrap;
    }

    /* Allineamento del titolo e del tipo */
    .card-title,
    .card-subtitle {
        text-align: center;
    }
</style>

<body>
<div class="container">
    <div class="card">
        <div class="row g-0">
            <div class="col-12">
                <div class="card-body">
                    <h1 id="game-title" class="card-title"></h1>
                    <h3 id="game-type" class="card-subtitle mb-2 text-muted"></h3>
                    <hr>
                    <img id="game-image" class="card-img" alt="Game Image">
                    <hr>
                    <p id="game-text" class="card-text"></p>
                    <hr>
                    <p class="card-text">
                        Prezzo: <span id="game-price"> <span id="price-value"></span></span>
                    </p>
                    <?php if (isset($_SESSION['email']) || isset($_COOKIE['email'])) { ?>
                        <div class="mb-3 mt-3">
                            <div class="d-flex align-items-center">
                                <label for="quantity" class="form-label me-2">Quantità:</label>
                                <div class="input-group" id="quantity-group">
                                    <button class="btn btn-outline-secondary" type="button" id="decrement">-</button>
                                    <input type="number" id="quantity" class="form-control" value="1" min="1" aria-label="Quantità">
                                    <button class="btn btn-outline-secondary" type="button" id="increment">+</button>
                                </div>
                            </div>
                            <label for="edition" class="form-label">Seleziona edizione:</label>
                            <select id="edition" class="form-select mb-3"></select>
                        </div>
                    <?php } ?>
                    <hr>
                </div>
            </div>
        </div>
    </div>
    <?php if (isset($_SESSION['email']) || isset($_COOKIE['email'])) { ?>
        <button style="margin-bottom: 4%;" class="btn btn-dark w-100">Aggiungi al carrello</button>
    <?php } ?>
</div>
<?php require '../references/footer.php' ?>
<script src="./prodotto/prodotto.js"></script>
</body>
</html>