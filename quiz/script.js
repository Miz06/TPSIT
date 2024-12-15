// Imposta la durata del countdown in minuti
const countdownDuration = 5; // Durata in minuti
const countdownDate = new Date().getTime() + countdownDuration * 60 * 1000; // Data di scadenza

// Aggiorna il countdown ogni secondo
const countdownInterval = setInterval(function () {
    const now = new Date().getTime();
    const distance = countdownDate - now;

    // Calcola minuti e secondi
    const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((distance % (1000 * 60)) / 1000);

    // Mostra il risultato nell'elemento countdown
    document.getElementById("countdown").innerHTML = `${minutes}m ${seconds}s`;

    // Se il countdown è finito, disabilita tutto e mostra un messaggio
    if (distance < 0) {
        clearInterval(countdownInterval);
        document.getElementById("countdown").innerHTML = "Countdown terminato!";
        disableAllInputs();
    }
}, 1000);

// Funzione per disabilitare tutti i campi input
function disableAllInputs() {
    // Disabilita tutte le radio buttons
    document.querySelectorAll('input[type="radio"]').forEach(input => input.disabled = true);

    // Disabilita tutte le textarea
    document.querySelectorAll('textarea').forEach(textarea => textarea.disabled = true);

    // Disabilita il pulsante submit
    const submitButton = document.querySelector('.btn-primary');
    if (submitButton) submitButton.disabled = true;

    alert("Il tempo è scaduto, risposte bloccate!");
}

// Funzione per mostrare un alert di conferma risposta
function showAlert(event) {
    event.preventDefault(); // Evita il comportamento predefinito del bottone (se necessario)

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

    // Disabilita le risposte della card
    const radios = parentCard.querySelectorAll('input[type="radio"]');
    radios.forEach(radio => radio.disabled = true);

    // Disabilita il bottone "Rispondi" (se presente)
    const submitButton = parentCard.querySelector('button');
    if (submitButton) submitButton.disabled = true;
}

// Funzione per salvare tutte le risposte
function submitAnswers() {
    let answers = ""; // Variabile per raccogliere tutte le risposte

    // Recupera tutte le domande con radio buttons
    const allQuestions = document.querySelectorAll('.card');
    allQuestions.forEach(question => {
        const questionText = question.querySelector('.card-header').textContent.trim();
        const selectedRadio = question.querySelector('input[type="radio"]:checked');
        
        if (selectedRadio) {
            answers += `${questionText}: ${selectedRadio.value}\n`;
        } else {
            answers += `${questionText}: Nessuna risposta selezionata\n`;
        }
    });

    // Recupera tutte le risposte aperte (textarea)
    const openQuestions = document.querySelectorAll('.carousel-item');
    openQuestions.forEach((question, index) => {
        const questionText = question.querySelector('.card-header').textContent.trim();
        const textarea = question.querySelector('textarea');
        
        if (textarea) {
            const answer = textarea.value.trim();
            answers += `Domanda ${index + 1}: ${answer || "Nessuna risposta inserita"}\n`;
        }
    });

    // Crea un file di testo con le risposte
    const blob = new Blob([answers], { type: "text/plain" });
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = "risposte.txt"; // Nome del file
    link.click(); // Simula il click per scaricare il file

    // Mostra un messaggio di conferma
    alert("Risposte salvate con successo!");

    // Disabilita tutte le risposte
    disableAllInputs();
}
