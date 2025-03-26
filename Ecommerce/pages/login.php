<?php
ob_start();
$title = 'login';
require '../references/navbar.php';

$config = require '../references/connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

$queryCheckLogin = 'SELECT email, password FROM db_Ecommerce.users WHERE email = :email';

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['email']) && isset($_POST['password'])) {
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
            header('Location: ./archivio.php');
        } else {
            $wrongCredentials = 'Credenziali errate! Riprovare';
        }

    } catch (Exception $e) {
        logError($e);
    }
}
ob_end_flush();
?>

<form method="post" action="login.php">
    <div class="element">
        <h4>Login</h4>
        <hr>

        <?php if(isset($_POST['email']) && isset($_POST['password']) && $wrongCredentials) {?>
            <p style="color: red"> <?php echo $wrongCredentials?></p>
        <?php }?>

        <label for="email"><strong>Email</strong></label>
        <input type="email" name="email" id="email" required>

        <br><br>
        <label for="password"><strong>Password</strong></label>
        <input type="password" name="password" id="password" required>

    </div>

    <div class="submit-container">
        <input type="submit" value="Accedi">
    </div>
</form>

<?php require '../references/footer.php';?>