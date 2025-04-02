<?php
ob_start();
$title = 'archivio';
require '../references/navbar.php';
require '../references/api.php';

$config = require '../references/connectionToDB/databaseConfig.php';;
$db = DBconn::getDB($config);

$querySelectItems =
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

<div class="container">
    <div class="row" id="card-container">
        <!-- Contenuto dell'archivio -->
    </div>
</div>

<?php require '../references/footer.php' ?>
<script src="./archivio/archivio.js"></script>

</body>
</html>