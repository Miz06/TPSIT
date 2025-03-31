<?php
$title = 'Carrello';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);
?>
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <title>Carrello</title>
    <link rel="stylesheet" href="path/to/your/styles.css">
    <style>
        .card {
            padding: 2%;
            margin: 8%;
            transition: transform 0.6s ease, box-shadow 0.6s ease;
            box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
            width: 100%;
        }
        .card img {
            width: 100%;
            height: 300px;
            object-fit: cover;
        }
        .card:hover {
            transform: scale(1.05);
            box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.3);
            cursor: pointer;
        }
    </style>
</head>
<body>
<div class="container mt-4 mb-4">
    <div id="cart-items" class="row">
        <!-- Qui verrà inserito il contenuto del carrello -->
    </div>
</div>

<?php require '../references/footer.php'; ?>

<!-- Se necessario, passa al JS alcuni dati di sessione (ma solo se non sono sensibili) -->
<script>
    const sessionEmail = "<?php echo $_SESSION['email'] ?? ''; ?>";
</script>
<!-- Carica il file JS -->
<script src="./carrello/carrello.js"></script>
</body>
</html>
