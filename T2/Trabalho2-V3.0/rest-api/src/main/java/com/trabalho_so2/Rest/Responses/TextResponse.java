package com.trabalho_so2.Rest.Responses;

import java.io.Serializable;
import lombok.Data;

/*
JSON
{
    text:String
}
*/

@Data
public class TextResponse implements Serializable{

    private final String text;

}
