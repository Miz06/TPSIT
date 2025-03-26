<?php
session_start();

if (isset($_SESSION['nome']) && isset($_SESSION['email']) && isset($_SESSION['nav_color'])) {
    setcookie('nome', $_SESSION['nome'], time() + 3600, "/", "", false, true);
    setcookie('email', $_SESSION['email'], time() + 3600, "/", "", false, true);
    setcookie('nav_color', $_SESSION['nav_color'], time() + 3600, "/", "", false, true);
    header('Location: ../pages/account.php');
} else {
    echo "Valori di sessione mancanti";
}
?>
