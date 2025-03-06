<?php
$title = 'registration_page';

require './db_connection/DBconn.php';
$config = require './db_connection/databaseConfig.php';
$db = DBconn::getDB($config);

$query = 'insert into db_Ecommerce(name, surname, email, username, pwd) values(:name, :surname, :email, :username, :pwd)';

$name = $_POST['name'];
$surname = $_POST['surname'];
$email = $_POST['email'];
$username = $_POST['username'];
$pwd = password_hash($_POST['pwd'], PASSWORD_DEFAULT);

    try {
        $stm = $db->prepare($query);
        $stm->bindValue(':name', $name);
        $stm->bindValue(':surname', $surname);
        $stm->bindValue(':email', $email);
        $stm->bindValue(':username', $username);
        $stm->bindValue(':pwd', $pwd);

        if ($stm->execute()) {
            header('Location: ./confirm.html');
        } else {
            throw new PDOException("Errore nella query");
        }

        $stm->closeCursor();
    } catch (Exception $e) {
        logError($e);
    }
?>

<form method="post" action="registration_page.php">
    <div class="card">
        <h1>Register</h1>

        <br>
        <label for="name"><strong>Name</strong></label>
        <input type ="text" id="name" name="name" required>
        <hr>

        <br>
        <label for="surname"><strong>Surname</strong></label>
        <input type ="text" id="surname" name="surname" required>
        <hr>

        <br>
        <label for="email"><strong>Email</strong></label>
        <input type ="email" id="email" name="email" required>
        <hr>

        <br>
        <label for="username"><strong>Username</strong></label>
        <input type ="text" id="username" name="username" required>
        <hr>

        <br>
        <label for="pwd"><strong>Password</strong></label>
        <input type ="password" id="pwd" name="pwd" required>
        <hr>
    </div>

    <input type="submit" class="submit-button" value="Register">
</form>
