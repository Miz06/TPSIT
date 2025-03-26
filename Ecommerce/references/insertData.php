<?php

require 'functions.php';
require './connectionToDB/DBconn.php';
$config = require './connectionToDB/databaseConfig.php';
$db = DBconn::getDB($config);

$queryInsertPersonale = 'INSERT INTO db_Ecommerce.users (email, name, password) VALUES (:email, :name, :password)';

$users = [
    // Sede Milano
    'a@gmail.com' => ['name' => 'Alessandro', 'password' => 'Password1!'],
    'b@gmail.com' => ['name' => 'Beppe', 'password' => 'Password2!'],
    'c@gmail.com' => ['name' => 'Carlo', 'password' => 'Password3!'],
];

function logError(PDOException $e): void
{
    error_log($e->getMessage().'---'.date('Y-m-d H:i:s'."\n"), 3,'./log/DB_Errors_log');
}

foreach ($users as $email => $userData) {
    try {
        $hashedPassword = password_hash($userData['password'], PASSWORD_DEFAULT);

        $stm = $db->prepare($queryInsertPersonale);

        $stm->bindValue(':email', $email);
        $stm->bindValue(':name', $userData['name']);
        $stm->bindValue(':password', $hashedPassword);

        $stm->execute();
        $stm->closeCursor();

        echo 'Utente ' . $email . ' inserito con successo nel DB <br>';
    } catch (Exception $e) {
        logError($e);
        echo 'Errore durante l\'inserimento dell\'utente ' . $email . ': ' . $e->getMessage() . '<br>';
    }
}
?>
