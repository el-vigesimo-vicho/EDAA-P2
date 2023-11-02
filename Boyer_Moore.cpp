#include<bits/stdc++.h>

int num_txt(std::vector<std::string> & patron){
    long long num=0;
    for(long long i=0;i<patron.size();i++){
        num = num+ patron[i].size();
    }
    return num;
}

void txt_to_vector_string(std::vector<std::string> & patron ,std::string & nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        exit(-1);
    }
    std::string linea;

    while (std::getline(archivo, linea)) {
        patron.push_back(linea);
    }
    // Cierra el archivo cuando hayas terminado de leerlo
    archivo.close();
}

void adjust(long long & iterador_str_texto,long long & iterador_substr_texto,long long & jump,std::vector<std::string> texto ){
    long long ajuste =  jump;
    for(long long i=0;i<texto.size();i++){
        if(ajuste -  (static_cast<long long>(texto[i].length()-1)) > 0) {
            ajuste = ajuste -  (static_cast<long long>(texto[i].length()-1));
        }else {
            iterador_str_texto= i;
            iterador_substr_texto = ajuste;
            break; 
        }
    }

}
bool verify(std::vector<std::string> & patron ,std::vector<std::string> & texto, long long iterador_str_texto,long long iterador_substr_texto, long long last_str_pat){
    bool res= false;
    bool no= true;
    for(long long i= last_str_pat; i >=0;i--){
        for(long long j = patron[i].length()-1;j>=0;j--){
           std::string pat= patron[i].substr(j,1);
           std::string tex= texto[iterador_str_texto].substr(iterador_substr_texto,1);
            if(patron[i].substr(j,1)== texto[iterador_str_texto].substr(iterador_substr_texto,1)){
                res=true;
            }else{
                res=false;
                no = false;
                break;
            }
            iterador_substr_texto--;
            if(iterador_substr_texto<0){
                no= false;
                break;
            }
        }
        if(not no)break;
        iterador_str_texto--;    
        if(iterador_str_texto<0)break;
    }
    return res;
}

long long find_in_table(std::map <std::string,long long> &m,std::string clave){
    auto b= clave;
    for (const auto& par : m) {
        if(par.first == clave)return par.second;
        auto a=par.first;
    }
    return -1;
}

int main(){
    long long cont_rep_pat=0;
    std::vector<std::string> patron;

    std::string nombreArchivo = "patron.txt"; 
    txt_to_vector_string(patron,nombreArchivo);
    
    std::vector<std::string> texto;
    nombreArchivo = "texto.txt";
    txt_to_vector_string(texto,nombreArchivo);


    std::map <std::string,long long> m;
    for(long long i=0;i<patron.size();i++){
        for(long long j=0;j<patron[i].size();j++){
            std::map<std::string, long long>::iterator it =m.find(patron[i].substr(j,1));
            if(it != m.end()){
                m.erase(patron[i].substr(j,1));
                m.insert(std::pair<std::string,long long>(patron[i].substr(j,1), ( j ) ));
            }else{
                m.insert(std::pair<std::string,long long>(patron[i].substr(j,1), ( j ) ));
            }
        }
    }
    std::map<std::string,long long>::iterator it = m.begin();
    for (it=m.begin(); it!=m.end(); ++it)std::cout << it->first << " => " << it->second << '\n';

    
    long long num_ch_patron=num_txt(patron);
    long long num_ch_texto=num_txt(texto);    

    if(num_ch_texto<num_ch_patron){
        std::cout<<"El patron es mas extenso que el texto\n";
        exit(-1);
    }

    long long others=num_ch_patron-1;

    std::string last_str_pat = patron[patron.size()-1];
    std::string last_ch_pat = last_str_pat.substr(last_str_pat.size()-1);

    long long jump = last_str_pat.size()-1;
    long long iterador_str_texto;
    long long iterador_substr_texto;
    while(jump<num_ch_texto-(texto.size()-1)){//se resta el text.size -1 debido a que corresponde a los saltos de lineas que no son caracteres pero si pertencen al texto
        adjust(iterador_str_texto,iterador_substr_texto,jump,texto);
        long long val_map= find_in_table(m,texto[iterador_str_texto].substr(iterador_substr_texto,1));
        auto c = texto[iterador_str_texto].substr(iterador_substr_texto,1);
        if(texto[iterador_str_texto].substr(iterador_substr_texto,1)==last_ch_pat){
            if(verify(patron,texto,iterador_str_texto,iterador_substr_texto,patron.size()-1)){
                std::cout<<"patron encontrado\n";
                cont_rep_pat++;
            }
            jump++;            
        }
        else if( val_map>0 ){
            jump+= others- val_map;
        }else{
            jump+=num_ch_patron;
        }  
    }
    std::cout<<cont_rep_pat<<std::endl;
    return 0;
}
