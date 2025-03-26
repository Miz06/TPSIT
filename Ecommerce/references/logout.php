<?php
session_start();

//Elimino la sessione
$_SESSION = [];
session_destroy();

// Elimino i cookies
if (isset($_COOKIE['nome'])) {
    setcookie('nome', '', time() - 3600, "/");
}

if (isset($_COOKIE['email'])) {
    setcookie('email', '', time() - 3600, "/");
}

if (isset($_COOKIE['nav_color'])) {
    setcookie('nav_color', '', time() - 3600, "/");
}

header('Location: ../pages/archivio.php');