<?php
ob_start();
$title = 'account';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

$queryCheckLogin = 'SELECT * FROM db_GameShop.users WHERE email = :email';

$wrongCredentials = "";

if (isset($_SESSION['email']) && isset($_POST['password_attuale'])) {
    try {
        $stm = $db->prepare($queryCheckLogin);
        $stm->bindValue(':email', $_SESSION['email']);
        $stm->execute();

        $userData = $stm->fetch(PDO::FETCH_ASSOC);
        $stm->closeCursor();

        if (password_verify($_POST['password_attuale'], $userData['password'])) {
            header('location: ../pages/aggiorna_password.php');
        } else {
            $wrongCredentials = "Password errata! Riprovare";
        }
    } catch (Exception $e) {
        logError($e);
    }
}

if (($_SERVER['REQUEST_METHOD'] == 'POST')) {
    //controllo navbar
    if (isset($_POST['nav_color'])) {
        $_SESSION['nav_color'] = $_POST['nav_color'];
        header("Location: ./account.php");
    }

    //controllo login
    if (isset($_POST['email']) && isset($_POST['password'])) {
        $email = $_POST['email'];
        $password = $_POST['password'];

        try {
            $stm = $db->prepare($queryCheckLogin);
            $stm->bindValue(':email', $email);
            $stm->execute();

            // Recupera i dati dell'utente
            $user = $stm->fetch(PDO::FETCH_ASSOC);
            $stm->closeCursor();

            if ($user && $email == $user['email'] && password_verify($password, $user['password'])) {
                $_SESSION['email'] = $_POST['email'];
                $_SESSION['nome'] = $user['name'];
                header("Location: ./account.php");
            } else {
                $wrongCredentials = 'Credenziali errate! Riprovare';
            }

        } catch (Exception $e) {
            logError($e);
        }
    }
}

ob_end_flush();
?>

<?php if (isset($_SESSION['email']) || isset($_SESSION['nome'])) { ?>
    <div class="element">
        <h4>Info account</h4>
        <hr>
        <p><strong>Nome: </strong> <?= $_SESSION['nome'] ?></p>
        <p><strong>Email: </strong> <?= $_SESSION['email'] ?></p>
    </div>

    <div class="element">

        <h4>Desideri cambiare password?</h4>
        <hr>
        <?php if (isset($_POST['password_attuale']) && $wrongCredentials) { ?>
            <p style="color: red"> <?php echo $wrongCredentials ?></p>
        <?php } ?>
        <p>[È prima necessario inserire la password in uso]</p>
        <form method="post" action="account.php">
            <label for="password_attuale"><strong>Password attuale</strong></label>
            <input type="password" name="password_attuale" id="password_attuale" required>

            <div class="submit-container">
                <input type="submit" value="Vai alla pagina di cambiamento password">
            </div>
        </form>
    </div>

    <div class="element">
        <form method="post" action="account.php">
            <h4><label for="nav_color">Desideri cambiare tema alla navbar?</label></h4>
            <hr>

            <div class="form-check">
                <input type="radio" id="grey" name="nav_color" value="darkslategrey" class="form-check-input">
                <label for="grey" class="form-check-label">Dark grey</label>
            </div>

            <div class="form-check">
                <input type="radio" id="blu" name="nav_color" value="darkblue" class="form-check-input">
                <label for="blu" class="form-check-label">Dark blu</label>
            </div>

            <div class="form-check">
                <input type="radio" id="nero" name="nav_color" value="#000000" class="form-check-input">
                <label for="nero" class="form-check-label">Nero</label>
            </div>

            <div class="submit-container">
                <input type="submit" value="Salva preferenze">
            </div>
        </form>
    </div>

    <div class="element">
        <h4>Salva le credenziali d'accesso</h4>
        <hr>
        <a href="../references/set_cookies.php" class="btn-primary btn">Salva credenziali</a>
    </div>

    <div class="element">
        <h4>Esci dall'account</h4>
        <hr>
        <a href="../references/logout.php" class="btn-primary log-out">Logout</a>
    </div>
<?php } else { ?>
    <div class="element">
        <p><strong>Nome: </strong>Ospite</p>
        <p>[NB: Dall'ccount ospite è possibile la sola visualizazione dei prodotti ma non il loro salvataggio nel
            carrello ed eventuale acquisto.]</p>
    </div>

    <form method="post" action="account.php">
        <div class="element">
            <h4>Accedi</h4>
            <hr>

            <?php if (isset($_POST['email']) && isset($_POST['password']) && $wrongCredentials) { ?>
                <p style="color: red"> <?php echo $wrongCredentials ?></p>
            <?php } ?>

            <label for="email"><strong>Email</strong></label>
            <input type="email" name="email" id="email" required>

            <br><br>
            <label for="password"><strong>Password</strong></label>
            <input type="password" name="password" id="password" required>

            <div class="submit-container">
                <input type="submit" value="Accedi">
            </div>
        </div>

        <div class="element">
            <h4>Non hai un account?</h4>
            <hr>
            <a href="./SignIn.php" class="btn btn-primary">Registrati</a>
        </div>
    </form>
<?php } ?>

<?php require '../references/footer.php'; ?>
