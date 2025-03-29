// Funzione per estrarre il prezzo da una stringa (es. "€10,99")
function parsePrice(priceStr) {
    const priceNumber = parseFloat(priceStr.replace(/[^\d.-]/g, ''));
    return isNaN(priceNumber) ? 0 : priceNumber;
}

// Funzione per renderizzare il carrello
function renderCart() {
    const cartItemsContainer = document.getElementById('cart-items');
    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];

    cartItemsContainer.innerHTML = '';  // Pulisce il contenitore del carrello

    if (cartItems.length === 0) {
        cartItemsContainer.innerHTML = '<p>Il carrello è vuoto.</p>';
    } else {
        let total = 0;
        let itemCount = 0;

        cartItems.forEach((item, index) => {
            const price = parsePrice(item.price);

            const itemCard = `
                <div class="col-md-4">
                    <div class="card mb-4 h-100">
                        <img src="${item.image}" class="card-img-top" alt="${item.title}">
                        <div class="card-body d-flex flex-column">
                            <h5 class="card-title">${item.title}</h5>
                            <p class="card-text">Edizione: ${item.edition || 'Standard'}</p>
                            <p class="card-text">${price.toFixed(2)} €</p>
                            <div class="d-flex align-items-center">
                                <span class="fw-bold me-2">Quantità:</span>
                                <span class="badge bg-secondary px-3 py-2">${item.quantity}</span>
                            </div>
                            <button class="btn btn-danger remove-item mt-3" data-index="${index}">Rimuovi</button>
                        </div>
                    </div>
                </div>
            `;
            cartItemsContainer.innerHTML += itemCard;

            total += price * item.quantity;
            itemCount += item.quantity;
        });

        let discount = 0;
        if (itemCount >= 3) {
            discount = total * 0.15;
            total -= discount;
        }

        const totalContainer = `
            <div class="col-12 mt-5 text-end">
                ${itemCount >= 3 ?
            `<br><hr><h4 class="text-decoration-line-through text-dark">Totale: €${(total + discount).toFixed(2)}</h4>` :
            `<br><hr><h4>Totale: €${total.toFixed(2)}</h4>`}
                ${itemCount >= 3 ? `<h5>Totale (15% di sconto su acquisti di 3 o più prodotti): €${total.toFixed(2)}</h5>` : ''}
            </div>
        `;
        cartItemsContainer.innerHTML += totalContainer;

        document.querySelectorAll('.remove-item').forEach(button => {
            button.addEventListener('click', (event) => {
                const index = event.target.getAttribute('data-index');
                cartItems.splice(index, 1);
                localStorage.setItem('cartItems', JSON.stringify(cartItems));
                renderCart();
            });
        });
    }
}

// Funzione per aggiungere un prodotto al carrello
function addToCart(newItem) {
    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];
    const existingItemIndex = cartItems.findIndex(item => item.title === newItem.title && item.edition === newItem.edition);
    if (existingItemIndex > -1) {
        cartItems[existingItemIndex].quantity += newItem.quantity;
    } else {
        cartItems.push(newItem);
    }
    localStorage.setItem('cartItems', JSON.stringify(cartItems));
    renderCart();
}

// Event listener per il caricamento della pagina
document.addEventListener('DOMContentLoaded', () => {
    renderCart();
});
