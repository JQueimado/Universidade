package com.test.ReactTest;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller 
public class HomeController {

	@RequestMapping(value = "/") 
	public String index() {
		return "index"; 
	}

}