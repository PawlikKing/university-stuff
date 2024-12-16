package com.example.controller;
import com.example.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
@Controller
public class ProductController {
@Autowired
private ProductService productService;
@GetMapping("/")
public String viewHomePage(Model model) {
model.addAttribute("listProducts", productService.listAll());
return "index";
}
// Inne mapowania (dodaj, edytuj, usuń)
}