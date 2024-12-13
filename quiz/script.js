// Imposta la durata del countdown in minuti
const countdownDuration = 5; // Durata in minuti
const countdownDate = new Date().getTime() + countdownDuration * 60 * 1000; // Data di scadenza

// Aggiorna il countdown ogni secondo
const x = setInterval(function () {
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

function showAlert(event) {
    event.preventDefault(); // Evita il comportamento predefinito (se necessario)
    
    // Crea il messaggio di successo
    const alertContainer = document.createElement('div');
    alertContainer.className = "alert alert-success d-flex align-items-center mt-3";
    alertContainer.setAttribute('role', 'alert');

    alertContainer.innerHTML = `
        <svg class="bi flex-shrink-0 me-2" role="img" aria-label="Success:">
            <use xlink:href="#check-circle-fill"></use>
        </svg>
        <div>
            Grazie di aver risposto!
        </div>
    `;

    // Aggiungi il messaggio di successo sotto la card
    const parentCard = event.target.closest('.card');
    parentCard.appendChild(alertContainer);

    // Disabilita le risposte (radio buttons)
    const radios = parentCard.querySelectorAll('input[type="radio"]');
    radios.forEach(radio => {
        radio.disabled = true;
    });

    // Rimuovi le etichette delle risposte (opzionale)
    const labels = parentCard.querySelectorAll('label');
    labels.forEach(label => {
        label.style.display = 'none';
    });

    // Disabilita il bottone "Invia"
    const submitButton = parentCard.querySelector('button');
    submitButton.disabled = true;
}
