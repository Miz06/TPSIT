<?php
ob_start();
$title = 'aggiorna password';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';; //utilizzo una sessione per evitare di fare nuovamente il require rispetto a $config (vedi navbar)
$db = DBconn::getDB($config);

$queryUpdatePassword = 'UPDATE db_Ecommerce.users SET password = :password WHERE email = :email';

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_SESSION['email'])) {
    if ($_POST['nuova_password'] == $_POST['conferma_nuova_password']) {
        $nuova_password = password_hash($_POST['nuova_password'], PASSWORD_DEFAULT);

        try {
            $stm = $db->prepare($queryUpdatePassword);
            $stm->bindValue(':password', $nuova_password);
            $stm->bindValue(':email', $_SESSION['email']);
            $stm->execute();
            $stm->closeCursor();

            header('Location: ./account.php');
        } catch (Exception $e) {
            logError($e);
        }
    } else {
        $wrongCredentials = 'Password differenti! Riprovare';
    }
}
ob_end_flush();
?>

<div class="element">
    <form method="post" action="aggiorna_password.php">
        <h4>Cambia password</h4>
        <hr>
        <?php if(isset($_POST['nuova_password']) && isset($_POST['conferma_nuova_password']) && $wrongCredentials) {?>
            <p style="color: red"> <?php echo $wrongCredentials?></p>
        <?php }?>
        <label for="nuova_password"><strong>Nuova password</strong></label>
        <input type="password" name="nuova_password" id="nuova_password" required>

        <br>
        <label for="conferma_nuova_password"><strong>Conferma nuova password</strong></label>
        <input type="password" name="conferma_nuova_password" id="conferma_nuova_password" required>

        <div class="submit-container">
            <input type="submit" value="Submit">
        </div>


    </form>
</div>

<?php require '../references/footer.php';?>