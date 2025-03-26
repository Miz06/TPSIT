<?php
session_start();

if (isset($_SESSION['nome']) && isset($_SESSION['email'])) {
    setcookie('nome', $_SESSION['nome'], time() + 3600, "/", "", false, true);
    setcookie('email', $_SESSION['email'], time() + 3600, "/", "", false, true);
    if($_SESSION['email'] = $_POST['email'])
        setcookie('nav_color', $_SESSION['nav_color'], time() + 3600, "/", "", false, true);
    header('Location: ../pages/account.php');
} else {
    echo "Valori di sessione mancanti";
}
