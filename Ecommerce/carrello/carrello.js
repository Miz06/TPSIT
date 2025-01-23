document.addEventListener('DOMContentLoaded', () => {
    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];
    const cartItemsContainer = document.getElementById('cart-items');

    if (cartItems.length === 0) { // Se non sono presenti elementi il carrello è vuoto
        cartItemsContainer.innerHTML = '<p>Il carrello è vuoto.</p>';
    } else {
        cartItems.forEach((item, index) => {
            const itemCard = `
                <div class="col-md-4">
                    <div class="card mb-4 h-100"> <!-- Aggiunta della classe h-100 -->
                        <img src="${item.image}" class="card-img-top" alt="${item.title}">
                        <div class="card-body d-flex flex-column"> <!-- Aggiunta di d-flex e flex-column -->
                            <h5 class="card-title">${item.title}</h5>
                            <p class="card-text">${item.price}</p>
                            <button class="btn btn-danger remove-item" data-index="${index}">Rimuovi</button>
                        </div>
                    </div>
                </div>
            `;
            cartItemsContainer.innerHTML += itemCard;
        });

        // Gestore di eventi per i pulsanti di rimozione
        const removeButtons = document.querySelectorAll('.remove-item');
        removeButtons.forEach(button => {
            button.addEventListener('click', (event) => {
                const index = event.target.getAttribute('data-index');
                cartItems.splice(index, 1); // Rimuovi l'elemento dall'array
                localStorage.setItem('cartItems', JSON.stringify(cartItems)); // Aggiorna il localStorage
                location.reload(); // Ricarica la pagina per aggiornare il carrello
            });
        });
    }
});