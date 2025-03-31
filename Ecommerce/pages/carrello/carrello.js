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
            console.log("Dati del carrello:", cartItems); // Debug: controlla i dati ricevuti
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
        const itemCard = `
            <div class="col-md-4">
                <div class="card mb-4 h-100">
                    <img src="${item.image}" class="card-img-top" alt="${item.title}">
                    <div class="card-body d-flex flex-column">
                        <h5 class="card-title">${item.title}</h5>
                        <p class="card-text">Edizione: ${item.edition_year}</p>
                        <p class="card-text">${price.toFixed(2)} €</p>
                        <div class="d-flex align-items-center">
                            <span class="fw-bold me-2">Quantità:</span>
                            <span class="badge bg-secondary px-3 py-2">${item.quantity}</span>
                        </div>
                        <button class="btn btn-danger remove-item mt-3" data-title="${item.title}" data-edition="${item.edition_year}">Rimuovi</button>
                    </div>
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
        </div>
    `;

    // Attacca il listener per la rimozione dell'item
    document.querySelectorAll('.remove-item').forEach(button => {
        button.addEventListener('click', event => {
            const title = event.target.getAttribute('data-title');
            const edition = event.target.getAttribute('data-edition');
            removeFromCart(title, edition);
        });
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
