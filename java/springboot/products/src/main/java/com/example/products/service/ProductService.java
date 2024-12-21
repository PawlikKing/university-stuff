package com.example.products.service;

import com.example.products.model.Product;
import com.example.products.repository.ProductRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class ProductService {

    @Autowired
    private ProductRepository productRepository;

    // Pobiera wszystkie produkty
    public List<Product> listAll() {
        return productRepository.findAll();
    }

    // Zapisuje lub aktualizuje produkt
    public void save(Product product) {
        System.out.println("Product received in save(): " + product); // Sprawdź dane
        if (product == null || product.getName() == null || product.getPrice() <= 0) {
            throw new IllegalArgumentException("Nieprawidłowe dane produktu!");
        }
        productRepository.save(product);
    }


    // Pobiera produkt po ID, z obsługą sytuacji, gdy produkt nie istnieje
    public Product get(Long id) {
        return productRepository.findById(id)
                .orElseThrow(() -> new RuntimeException("Produkt o ID " + id + " nie istnieje!"));
    }

    // Usuwa produkt po ID
    public void delete(Long id) {
        if (!productRepository.existsById(id)) {
            throw new RuntimeException("Nie można usunąć produktu, ponieważ ID " + id + " nie istnieje!");
        }
        productRepository.deleteById(id);
    }
}
