document.addEventListener('DOMContentLoaded', () => {
    const cardData = JSON.parse(localStorage.getItem('selectedCard'));

    if (cardData) {
        document.querySelector('#game-title').textContent = cardData.title;
        document.querySelector('#game-type').textContent = cardData.type;
        document.querySelector('#game-image').src = cardData.image;
        document.querySelector('#price-value').textContent = cardData.price;
        document.querySelector('#game-text').textContent = cardData.text;

        // Popola il menu a tendina con le edizioni disponibili
        const editionSelect = document.querySelector('#edition');
        cardData.editions.forEach(edition => {
            const option = document.createElement('option');
            option.value = edition;
            option.textContent = edition;
            editionSelect.appendChild(option);
        });
    }

    // Logica incrementa/decrementa
    const quantityInput = document.querySelector('#quantity');
    const incrementButton = document.querySelector('#increment');
    const decrementButton = document.querySelector('#decrement');

    incrementButton.addEventListener('click', () => {
        quantityInput.value = parseInt(quantityInput.value) + 1;
    });

    decrementButton.addEventListener('click', () => {
        if (parseInt(quantityInput.value) > 1) {
            quantityInput.value = parseInt(quantityInput.value) - 1;
        }
    });

    // Logica aggiungi al carrello e salvataggio nel database
    const addToCartButton = document.querySelector('.btn-dark');

    addToCartButton.addEventListener('click', () => {
        const quantity = parseInt(quantityInput.value); // Leggi la quantità selezionata
        const selectedEdition = document.querySelector('#edition').value;

        if (quantity < 1) {
            alert('La quantità deve essere almeno 1.');
            return;
        }

        const productWithQuantity = { ...cardData, quantity, edition: selectedEdition };
        const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];

        // Verifica se il prodotto con la stessa edizione esiste già nel carrello
        const existingItemIndex = cartItems.findIndex(item => item.title === productWithQuantity.title && item.edition === productWithQuantity.edition);
        if (existingItemIndex > -1) {
            cartItems[existingItemIndex].quantity += productWithQuantity.quantity;
        } else {
            cartItems.push(productWithQuantity);
        }

        // Salva il carrello aggiornato nel localStorage
        localStorage.setItem('cartItems', JSON.stringify(cartItems));

        fetch('./prodotto.php', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                title: cardData.title,
                edition_year: selectedEdition,
                quantity: quantity // Aggiunge la quantità selezionata
            })
        })

            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    console.log('Prodotto salvato nel database');
                } else {
                    console.error('Errore:', data.message);
                }
            })
            .catch(error => console.error('Errore:', error));

        // Redirect alla pagina del carrello
        window.location.href = '../pages/carrello.php';
    });
});
