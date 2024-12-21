package com.example.products.controller;
import com.example.products.model.Product;
import com.example.products.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

import java.util.List;

@Controller
public class ProductController {
    @Autowired
    private ProductService productService;

    @GetMapping("/")
    public String viewHomePage(Model model) {
        List<Product> products = productService.listAll();
        System.out.println("Products: " + products); // Logowanie listy produktów
        model.addAttribute("listProducts", products);
        return "index";
    }

    @GetMapping("/new")
    public String showNewProductForm(Model model) {
        model.addAttribute("product", new Product());
        return "new_product";
    }

    @PostMapping("/save")
    public String saveProduct(@ModelAttribute("product") Product product, Model model) {
        try {
            productService.save(product);
        } catch (IllegalArgumentException e) {
            model.addAttribute("errorMessage", e.getMessage());
            return "new_product"; // Powrót do formularza z błędem
        }
        return "redirect:/";
    }

    @GetMapping("/edit/{id}")
    public String showEditProductForm(@PathVariable("id") Long id, Model model) {
        try {
            Product product = productService.get(id);
            model.addAttribute("product", product);
        } catch (RuntimeException e) {
            model.addAttribute("errorMessage", e.getMessage());
            return "error"; // Wyświetl szablon błędu
        }
        return "edit_product";
    }

    @GetMapping("/delete/{id}")
    public String deleteProduct(@PathVariable("id") Long id, Model model) {
        try {
            productService.delete(id);
        } catch (RuntimeException e) {
            model.addAttribute("errorMessage", e.getMessage());
            return "error"; // Wyświetl szablon błędu
        }
        return "redirect:/";
    }
}
