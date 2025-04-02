document.addEventListener('DOMContentLoaded', () => {
    loadCart();
});

function loadCart() {
    fetch('./carrello/getCart.php', { credentials: 'same-origin' })
        .then(response => {
            if (!response.ok) {
                throw new Error(`Errore nel recupero del carrello: ${response.statusText}`);
            }
            return response.json();
        })
        .then(cartItems => {
            console.log("Dati del carrello:", cartItems);
            renderCart(cartItems);
        })
        .catch(error => console.error('Errore nel caricamento del carrello:', error));
}

function renderCart(cartItems) {
    const cartItemsContainer = document.getElementById('cart-items');
    cartItemsContainer.innerHTML = '';

    if (cartItems.length === 0) {
        cartItemsContainer.innerHTML = '<p>Il carrello è vuoto.</p>';
        return;
    }

    let total = 0;
    let itemCount = 0;

    cartItems.forEach(item => {
        const price = parseFloat(item.price);
        // NOTA: abbiamo rimosso il bottone "Acquista" dalla card,
        // lasciando solo il checkbox per la selezione
        const itemCard = `
            <div class="col-md-4">
                <div class="card mb-4">
                    <img src="${item.image}" class="card-img-top" alt="${item.title}">
                    <div class="card-body d-flex flex-column">
                        <h5 class="card-title">${item.title}</h5>
                        <p class="card-text">Edizione: ${item.edition_year}</p>
                        <p class="card-text">${price.toFixed(2)} €</p>
                        <div class="d-flex align-items-center">
                            <span class="fw-bold me-2">Quantità:</span>
                            <span class="badge bg-secondary px-3 py-2">${item.quantity}</span>
                        </div>
                        <div class="form-check mt-2">
                            <input class="form-check-input select-item" type="checkbox" data-title="${item.title}" data-edition="${item.edition_year}" data-quantity="${item.quantity}">
                            <label class="form-check-label">Seleziona per l'acquisto</label>
                        </div>
                    </div>
                    <button class="btn btn-danger remove-item mt-3" data-title="${item.title}" data-edition="${item.edition_year}">Rimuovi</button>
                </div>
            </div>
        `;
        cartItemsContainer.innerHTML += itemCard;
        total += price * item.quantity;
        itemCount += item.quantity;
    });

    // Applica lo sconto se la quantità totale è almeno 3
    if (itemCount >= 3) {
        total *= 0.85;
    }

    cartItemsContainer.innerHTML += `
        <div class="col-12 mt-5 text-end">
            <hr>
            <h4>Totale: €${total.toFixed(2)}</h4>
            <button id="buy-selected" class="btn btn-success mt-3">Acquista Selezionati</button>
        </div>
    `;

    // Aggiunge il listener per i bottoni "Rimuovi"
    document.querySelectorAll('.remove-item').forEach(button => {
        button.addEventListener('click', event => {
            event.stopPropagation();
            const title = event.target.getAttribute('data-title');
            const edition = event.target.getAttribute('data-edition');
            removeFromCart(title, edition);
        });
    });

    // Aggiunge il listener per il cambio stato dei checkbox: evidenzia la card selezionata
    document.querySelectorAll('.select-item').forEach(checkbox => {
        checkbox.addEventListener('change', event => {
            const card = event.target.closest('.card');
            if (event.target.checked) {
                card.classList.add('selected');
            } else {
                card.classList.remove('selected');
            }
        });
    });

    // Listener per il bottone "Acquista Selezionati"
    document.getElementById('buy-selected').addEventListener('click', () => {
        const selectedItems = [];
        document.querySelectorAll('.select-item:checked').forEach(checkbox => {
            selectedItems.push({
                title: checkbox.getAttribute('data-title'),
                edition: checkbox.getAttribute('data-edition'),
                quantity: checkbox.getAttribute('data-quantity')
            });
        });

        if (selectedItems.length === 0) {
            alert("Seleziona almeno un prodotto per procedere all'acquisto!");
            return;
        }

        buySelectedItems(selectedItems);
    });
}

function removeFromCart(title, edition) {
    fetch('./carrello/removeItem.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'same-origin',
        body: JSON.stringify({ title, edition })
    })
        .then(response => {
            if (!response.ok) {
                throw new Error(`Errore nella rimozione: ${response.statusText}`);
            }
            return response.json();
        })
        .then(data => {
            if (data.success) {
                loadCart();
            } else {
                console.error('Errore nella rimozione:', data.error);
            }
        })
        .catch(error => console.error('Errore:', error));
}

function buySelectedItems(selectedItems) {
    fetch('./carrello/buyItem.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        credentials: 'same-origin',
        body: JSON.stringify({ items: selectedItems })
    })
        .then(response => {
            if (!response.ok) {
                throw new Error(`Errore nell'acquisto: ${response.statusText}`);
            }
            return response.json();
        })
        .then(data => {
            if (data.success) {
                console.log('Acquisto completato con successo.');
                loadCart();
                showGreenAlert();
            } else {
                console.error('Errore nell\'acquisto:', data.error);
            }
        })
        .catch(error => console.error('Errore:', error));
}

function showGreenAlert() {
    const greenAlert = document.getElementById('green-alert');
    greenAlert.style.display = 'block';
    setTimeout(() => {
        greenAlert.style.display = 'none';
    }, 3000);
}
