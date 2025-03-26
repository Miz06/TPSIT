<?php
ob_start();
$title = 'Registrazione';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

$queryInsertUser = 'INSERT INTO db_Ecommerce.users (email, name , password) VALUES (:email, :name, :password)';
$queryCheckLogin = 'SELECT email FROM db_Ecommerce.users WHERE email = :email';

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['email']) && isset($_POST['name']) && isset($_POST['password'])) {
    $email = $_POST['email'];
    $name = $_POST['name'];

    try {
        $stm = $db->prepare($queryCheckLogin);
        $stm->bindValue(':email', $email);
        $stm->execute();

        // Recupera i dati dell'utente
        $user = $stm->fetch(PDO::FETCH_ASSOC);
        $stm->closeCursor();

        if (!$user || $email == $user['email']) {
            try{
                $password = password_hash($_POST['password'],  PASSWORD_DEFAULT);

                $stm = $db->prepare($queryInsertUser);

                $stm->bindValue(':email', $email);
                $stm->bindValue(':name', $name);
                $stm->bindValue(':password', $password);

                $stm->execute();
                $_SESSION['email'] = $_POST['email'];
                header('Location: ./archivio.php');
            }catch (Exception $e){
                logError($e);
            }
        } else {
            $wrongCredentials = 'Utente già registrato con questa email! Riprovare.';
        }

    } catch (Exception $e) {
        logError($e);
    }
}
ob_end_flush();
?>
    <form method="post" action="SignIn.php">
        <div class="element">
            <h4>Registrati</h4>
            <hr>

            <?php if (isset($wrongCredentials)) { ?>
                <p style="color: red"> <?php echo $wrongCredentials; ?></p>
            <?php } ?>

            <label for="email"><strong>Email</strong></label>
            <input type="email" name="email" id="email" required>

            <br><br>
            <label for="name"><strong>Nome</strong></label>
            <input type="text" name="name" id="name" required>

            <br><br>
            <label for="password"><strong>Password</strong></label>
            <input type="password" name="password" id="password" required>

        </div>

        <div class="submit-container">
            <input type="submit" value="Registrati">
        </div>
    </form>

<?php require '../references/footer.php'; ?>