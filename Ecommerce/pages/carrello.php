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
            transition: transform 0.6s ease, box-shadow 0.6s ease, border 0.6s ease;
            box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
            width: 100%;
            border: 2px solid transparent;
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
        /* Evidenziazione delle card selezionate: bordo sfumato */
        .card.selected {
            border: 2px solid;
            border-image: linear-gradient(45deg, #1abc9c, #3498db) 1;
            box-shadow: 0 0 15px rgba(52, 152, 219, 0.6);
        }
    </style>
</head>
<body>
<div class="container mt-4 mb-4">
    <div id="green-alert" class="alert" style="display: none; position: fixed; top: 50%; left: 50%; transform: translate(-50%, -50%); z-index: 1000;">
        Operazione avvenuta con successo!
    </div>
    <div id="cart-items" class="row">
        <!-- Contenuto del carrello caricato via JS -->
    </div>
</div>

<?php require '../references/footer.php'; ?>

<script>
    const sessionEmail = "<?php echo $_SESSION['email'] ?? ''; ?>";
</script>
<!-- Carica il file JS aggiornato -->
<script src="./carrello/carrello.js"></script>
</body>
</html>
