document.addEventListener("DOMContentLoaded", () => {
    // Load the JSON data
    fetch('./data.json')
      .then(response => response.json())
      .then(data => {
        populateNavbar(data.navbar);
        populateFooter(data.footer);
      });
  
    function populateNavbar(navbarData) {
      const navbar = document.createElement('nav');
      navbar.className = 'navbar bg-black';
      navbar.innerHTML = `
        <div class="container-fluid">
          <h1 class="navbar-brand text-white">${navbarData.brand}</h1>
          <button class="navbar-toggler" type="button" data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar" aria-controls="offcanvasNavbar">
            <span class="navbar-toggler-icon"></span>
          </button>
          <div class="offcanvas offcanvas-end" tabindex="-1" id="offcanvasNavbar" aria-labelledby="offcanvasNavbarLabel">
            <div class="offcanvas-header">
              <h5 class="offcanvas-title text-black" id="offcanvasNavbarLabel">${navbarData.brand}</h5>
              <button type="button" class="btn-close" data-bs-dismiss="offcanvas" aria-label="Close"></button>
            </div>
            <div class="offcanvas-body">
              <ul class="navbar-nav justify-content-end flex-grow-1 pe-3">
                ${navbarData.links
                  .map(
                    link => `
                  <li class="nav-item">
                    <a class="nav-link text-dark" href="${link.href}">${link.name}</a>
                  </li>`
                  )
                  .join('')}
              </ul>
            </div>
          </div>
        </div>
      `;
      document.body.prepend(navbar);
    }
  
    function populateFooter(footerData) {
      const footer = document.createElement('footer');
      footer.innerHTML = `
        <div class="bg-black p-4 text-center">
          <p class="display-10 mb-2 text-white">${footerData.text}</p>
        </div>
      `;
      document.body.appendChild(footer);
    }
  });
  