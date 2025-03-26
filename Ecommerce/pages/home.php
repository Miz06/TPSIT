<?php
ob_start();
$title = 'home';
require '../references/navbar.php';

use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require '../vendor/autoload.php';

$successMessage = ''; // Variabile per il messaggio di successo

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['nome']) && isset($_POST['email']) && isset($_POST['content'])) {
    $nome = $_POST['nome'];
    $email = $_POST['email'];
    $content = $_POST['content'];

    $mail = new PHPMailer(true);

    try {
        $mail->isSMTP(); // Protocollo mail
        $mail->Host = 'smtp.gmail.com'; // Mail SMTP server
        $mail->SMTPAuth = true; // Autorizzazione
        $mail->Username = 'alessandro.mizzon@iisviolamarchesini.edu.it';
        $mail->Password = 'tonx fxgh pguo erde';
        $mail->SMTPSecure = PHPMailer::ENCRYPTION_STARTTLS; // Sicurezza
        $mail->Port = 587;
        $mail->setFrom('alessandro.mizzon@iisviolamarchesini.edu.it');
        $mail->addAddress('alessandro.mizzon@iisviolamarchesini.edu.it');
        $mail->Subject = 'Question from ' . $nome . ' (' . $email . ')';
        $mail->Body = $content;
        $mail->CharSet = 'UTF-8';
        $mail->Encoding = 'base64';
        $mail->send();

        header('Location: ./home.php');
    } catch (Exception $e) {
        logError($e);
    }
    ob_end_flush();
}
?>
    <div class="element">
        <form method="post" action="home.php">
            <h4>Contattaci</h4>
            <hr>

            <br>
            <label for="nome"><strong>Il tuo nome</strong></label>
            <?php if (isset($_SESSION['nome']) || isset($_COOKIE['email'])){ ?>
                <input type="text" name="nome" id="nome" value="<?php echo $_SESSION['nome'] ?>" required>
            <?php }else {?>
                <input type="text" name="nome" id="nome" required>
            <?php }?>

            <br><br>
            <label for="email"><strong>La tua email</strong></label>
            <?php if (isset($_SESSION['nome'])){ ?>
                <input type="text" name="email" id="email" value="<?php echo $_SESSION['email'] ?>" required>
            <?php }else {?>
                <input type="email" name="email" id="email" required>
            <?php }?>

            <br><br>
            <label for="content"><strong>Contenuto della email</strong></label>
            <input type="text" name="content" id="content" required>

            <div class="submit-container">
                <input type="submit" value="Invia email al team Fast Route">
            </div>
        </form>
    </div>

<?php if ($successMessage): ?>
    <div class="alert alert-success" style="color: green; margin-top: 2%; border-radius: 5px">
        <?php echo $successMessage; ?>
    </div>
<?php endif; ?>

<?php require '../references/footer.php'; ?>