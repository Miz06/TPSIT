// Imposta la durata del countdown in minuti
const countdownDuration = 5; // Durata in minuti
const countdownDate = new Date().getTime() + countdownDuration * 60 * 1000; // Data di scadenza

// Aggiorna il countdown ogni secondo
const x = setInterval(function() {
    const now = new Date().getTime();
    const distance = countdownDate - now;

    // Calcola minuti e secondi
    const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((distance % (1000 * 60)) / 1000);

    // Mostra il risultato nel elemento countdown
    document.getElementById("countdown").innerHTML = minutes + "m " + seconds + "s ";

    // Se il countdown è finito, mostra un messaggio
    if (distance < 0) {
        clearInterval(x);
        document.getElementById("countdown").innerHTML = "Countdown terminato!";
    }
}, 1000);