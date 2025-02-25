document.addEventListener('DOMContentLoaded', () => {
  const cardData = JSON.parse(localStorage.getItem('selectedCard'));

  if (cardData) {
    document.querySelector('#game-title').textContent = cardData.title;
    document.querySelector('#game-type').textContent = cardData.type;
    document.querySelector('#game-image').src = cardData.image;
    document.querySelector('#price-value').textContent = cardData.price;
    document.querySelector('#game-text').textContent = cardData.text;
  }

  // Increment/Decrement quantity logic
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

  // Add to cart button logic
  const addToCartButton = document.querySelector('.btn-dark');
  addToCartButton.addEventListener('click', () => {
    const quantity = quantityInput.value;

    if (quantity < 1) {
      alert('La quantità deve essere almeno 1.');
      return;
    }

    const productWithQuantity = { ...cardData, quantity: parseInt(quantity) };

    const cartItems = JSON.parse(localStorage.getItem('cartItems')) || [];

    // Verifica se il prodotto esiste già nel carrello
    const existingItemIndex = cartItems.findIndex(item => item.title === productWithQuantity.title);
    if (existingItemIndex > -1) {
      // Se il prodotto esiste già, somma la quantità
      cartItems[existingItemIndex].quantity += productWithQuantity.quantity;
    } else {
      // Altrimenti, aggiungi il nuovo prodotto
      cartItems.push(productWithQuantity);
    }

    // Salva il carrello aggiornato nel localStorage
    localStorage.setItem('cartItems', JSON.stringify(cartItems));

    // Redirect alla pagina del carrello
    window.location.href = '../carrello/carrello.html'; // Redirect to cart page
  });
});
