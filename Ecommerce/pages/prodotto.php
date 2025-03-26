<?php
ob_start();
$title = 'prodotto';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';;
$db = DBconn::getDB($config);

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
        /* Permette al gruppo di input di adattarsi al contenuto */
        border: 2px solid #007bff;
        /* Colore del bordo */
        border-radius: 10px;
        /* Angoli arrotondati */
        overflow: hidden;
        /* Nascondi gli angoli */
    }

    .input-group .form-control {
        width: 40px;
        /* Riduci la larghezza del campo di input */
        padding: 5px;
        /* Riduci il padding per un aspetto più compatto */
        font-size: 14px;
        /* Dimensione del font più piccola */
        text-align: center;
        /* Centra il testo all'interno del campo */
        border: none;
        /* Rimuovi il bordo */
    }

    .input-group button {
        width: 30px;
        /* Riduci la larghezza dei pulsanti */
        font-size: 14px;
        /* Dimensione del font più piccola */
        background-color: #007bff;
        /* Colore di sfondo blu */
        color: white;
        /* Testo bianco */
        border: none;
        /* Rimuovi il bordo */
    }

    .input-group button:hover {
        background-color: #0056b3;
        /* Colore di sfondo blu scuro al passaggio del mouse */
    }

    /* Stile per il prezzo */
    #game-price {
        border: 2px solid green;
        /* Contorno verde */
        padding: 5px;
        /* Padding interno */
        border-radius: 10px;
        /* Angoli arrotondati */
        display: inline-block;
        /* Limita la larghezza al contenuto */
        white-space: nowrap;
        /* Impedisce il wrapping del testo */
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
                                 <input type="number" id="quantity" class="form-control" value="1" min="1"
                                           aria-label="Quantità">
                                    <button class="btn btn-outline-secondary" type="button" id="increment">+</button>
                            </div>
                        </div>
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