let countdownInterval; // Variabile globale per l'intervallo del countdown

// Disabilita tutti i campi input
function disableAllInputs() {
    document.querySelectorAll('input[type="radio"], textarea').forEach(input => input.disabled = true);

    const submitButton = document.querySelector('.btn-primary');
    if (submitButton) submitButton.disabled = true;
}

// Impostazione del countdown all'interno di caricaComponenti
function startCountdown(duration) {
    const countdownDate = new Date().getTime() + duration * 60 * 1000;
    countdownInterval = setInterval(() => {
        const now = new Date().getTime();
        const distance = countdownDate - now;

        const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
        const seconds = Math.floor((distance % (1000 * 60)) / 1000);

        document.getElementById("countdown").innerHTML = `${minutes}m ${seconds}s`;

        if (distance < 0) {
            document.getElementById("countdown").innerHTML = "Countdown terminato!";
            disableAllInputs();
            clearInterval(countdownInterval); // Ferma il countdown quando scade
        }
    }, 1000);
}

// Genera e salva le risposte
function submitAnswers() {
    let answers = "~~~ RISPOSTE APERTE ~~~\n";

    document.querySelectorAll('.carousel-item textarea').forEach((textarea, index) => {
        answers += `Domanda ${index + 1}: ${textarea.value.trim() || "Nessuna risposta inserita"}\n`;
    });

    answers += "\n~~~ RISPOSTE CHIUSE ~~~\n";
    document.querySelectorAll('#multipleChoiceContainer .card').forEach(card => {
        const questionText = card.querySelector('.card-header').textContent.trim();
        const selectedOption = card.querySelector('input[type="radio"]:checked');
        answers += `${questionText}: ${selectedOption ? selectedOption.nextElementSibling.textContent : "Nessuna risposta selezionata"}\n`;
    });

    const blob = new Blob([answers], { type: "text/plain" });
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = "risposte.txt";
    link.click();

    // Disabilita tutti i campi input
    disableAllInputs();
    // Mostra il messaggio finale e ferma il countdown
    document.getElementById("countdown").innerHTML = "Quiz terminato con successo!";
    clearInterval(countdownInterval); // Ferma il countdown quando termina il quiz
}

// Funzione per caricare la navbar, il footer e l'alert
function caricaComponenti() {
    // Carica tutto il JSON
    fetch('./script.json')
        .then(response => response.json())
        .then(data => {
            // Carica la durata del countdown e avvia il countdown
            const countdownDuration = data.countdown.duration;
            startCountdown(countdownDuration);

            // Carica la navbar
            const navbarContainer = document.getElementById('navbarContainer');
            navbarContainer.innerHTML = data.navbar
                .map(item => `<a href="${item.link}">${item.label}</a>`)
                .join(' | ');

            // Carica il footer
            const footerContainer = document.getElementById('footerContainer');
            footerContainer.innerHTML = data.footer.text.map(line => `<p>${line}</p>`).join('');

            // Carica l'alert sotto il countdown
            if (data.alert) {
                const alertContainer = document.createElement('div');
                alertContainer.className = `alert alert-${data.alert.type} text-center`;
                alertContainer.setAttribute('role', 'alert');
                alertContainer.innerText = data.alert.message;
                // Posiziona l'alert dopo il countdown
                const countdownElement = document.getElementById("countdown");
                countdownElement.parentNode.insertBefore(alertContainer, countdownElement.nextSibling);
            }

            // Carica le domande
            const carouselInner = document.getElementById('carouselInner');
            const carouselIndicators = document.getElementById('carouselIndicators');
            const multipleChoiceContainer = document.getElementById('multipleChoiceContainer');

            data.domande.forEach((domanda, index) => {
                if (domanda.tipo === 'testo') {
                    // Carosello per domande a risposta aperta
                    const item = document.createElement('div');
                    item.className = `carousel-item ${index === 0 ? 'active' : ''}`;
                    item.innerHTML = `  
                        ${domanda.immagine ? `<img src="${domanda.immagine}" class="d-block w-100" alt="Domanda ${index + 1}">` : ''} 
                        <div class="carousel-caption d-none d-md-block">
                            <div class="card text-center" style="border: 1px solid black">
                                <div class="card-header">Domanda ${index + 1}</div>
                                <div class="card-body">
                                    <p class="card-text">${domanda.testo}</p>
                                    <textarea class="form-control mt-2" rows="3" placeholder="Inserisci la tua risposta qui..."></textarea>
                                </div>
                            </div>
                        </div>`;
                    carouselInner.appendChild(item);

                    const indicator = document.createElement('button');
                    indicator.type = 'button';
                    indicator.className = `carousel-indicator ${index === 0 ? 'active' : ''}`;
                    indicator.setAttribute('data-bs-target', '#carouselExampleCaptions');
                    indicator.setAttribute('data-bs-slide-to', index);
                    indicator.setAttribute('aria-label', `Slide ${index + 1}`);
                    carouselIndicators.appendChild(indicator);
                } else if (domanda.tipo === 'scelta') {
                    // Risposta multipla
                    const card = document.createElement('div');
                    card.className = 'card mt-4';
                    card.style.border = '1px solid black';
                    card.innerHTML = ` 
                        <div class="card-header">Domanda ${index + 1}</div>
                        <div class="card-body">
                            <p class="card-text">${domanda.testo}</p>
                            ${domanda.opzioni.map((opzione, idx) => `
                                <div class="form-check">
                                    <input class="form-check-input" type="radio" name="domanda${domanda.id}" id="domanda${domanda.id}-opzione${idx}" value="${opzione.id}">
                                    <label class="form-check-label" for="domanda${domanda.id}-opzione${idx}">${opzione.testo}</label>
                                </div>`).join('')}
                        </div>`;
                    multipleChoiceContainer.appendChild(card);
                }
            });

        })
        .catch(error => console.error('Errore nel caricare il JSON:', error));
}

// Carica tutto all'avvio della pagina
window.addEventListener('load', () => {
    caricaComponenti();
});
