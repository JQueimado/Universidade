package EDA1;

import java.util.ArrayList;

public class HashElement<T> {
	public T elemento;
	public boolean ativo;
	public ArrayList<String> sugestoes;
	
	public HashElement(T o){
		this.elemento=o;
		this.ativo=true;
		sugestoes=new ArrayList<String>();
	}
	
	public void addlist(String s){
		sugestoes.add(s);
	}
	public boolean getAtivo(){ //retorna se um elemento est� ativo na hash
		return ativo;
	}
		
	public T getElemento(){ //retorna o elemento
		return elemento;
	}
	
	public void setElemento(T elem){ //poe um elemento na hash
		elemento=elem; 
	}
	public void setAtivo(boolean ative){ //poe um elemento ativo
		ativo=ative;
	}
	
	public String toString(){ //passa os elementos para sting
		return (String) elemento;
	}
	
}
