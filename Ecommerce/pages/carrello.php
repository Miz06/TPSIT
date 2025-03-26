<?php
ob_start();
$title = 'carrello';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';;
$db = DBconn::getDB($config);

ob_end_flush();
?>
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

<body>
<div class="container mt-4 mb-4">
    <div id="cart-items" class="row">
        <!-- Contenuto del carrello -->
    </div>
</div>

<?php require '../references/footer.php' ?>
<script src="./carrello/carrello.js"></script>

</body>
</html>