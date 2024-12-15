// Impostazione del countdown
const countdownDuration = 5; // Durata in minuti
const countdownDate = new Date().getTime() + countdownDuration * 60 * 1000;

// Aggiorna il countdown ogni secondo
const countdownInterval = setInterval(() => {
    const now = new Date().getTime();
    const distance = countdownDate - now;

    const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((distance % (1000 * 60)) / 1000);

    document.getElementById("countdown").innerHTML = `${minutes}m ${seconds}s`;

    if (distance < 0) {
        document.getElementById("countdown").innerHTML = "Countdown terminato!";
        disableAllInputs();
        clearInterval(countdownInterval);
    }
}, 1000);

// Disabilita tutti i campi input
function disableAllInputs() {
    document.querySelectorAll('input[type="radio"], textarea').forEach(input => input.disabled = true);

    const submitButton = document.querySelector('.btn-primary');
    if (submitButton) submitButton.disabled = true;
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

    disableAllInputs();
    document.getElementById("countdown").innerHTML = "Quiz terminato con successo!";
    clearInterval(countdownInterval);
}

// Caricamento domande
function caricaDomande() {
    fetch('domande.json')
        .then(response => response.json())
        .then(data => {
            const { domande } = data;
            const carouselInner = document.getElementById('carouselInner');
            const carouselIndicators = document.getElementById('carouselIndicators');
            const multipleChoiceContainer = document.getElementById('multipleChoiceContainer');

            domande.forEach((domanda, index) => {
                if (domanda.tipo === 'testo') {
                    // Carosello
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
                                </div>
                            `).join('')}
                        </div>`;
                    multipleChoiceContainer.appendChild(card);
                }
            });
        })
        .catch(error => console.error('Errore nel caricare il JSON:', error));
}

window.addEventListener('load', caricaDomande);
