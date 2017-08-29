package main;

public class AI {
    
    private static int verifyRows(int[][] symbols){
        int xqtt, oqtt;
        for (int i=0;i<symbols.length;i++){
            xqtt = oqtt = 0;
            for (int j=0;j<symbols.length;j++){
                if (symbols[i][j]==1)oqtt++;
                else if (symbols[i][j]==2)xqtt++;
            }
            if (oqtt==3)return 2;
            if (xqtt==3)return 1;
        }
        return 0;
    }
    
    private static int verifyCollums(int[][] symbols){
        int xqtt, oqtt;
        for (int i=0;i<symbols.length;i++){
            xqtt = oqtt = 0;
            for (int j=0;j<symbols.length;j++){
                if (symbols[j][i]==1)oqtt++;
                else if (symbols[j][i]==2)xqtt++;
            }
            if (oqtt==3)return 2;
            if (xqtt==3)return 1;
        }
        return 0;
    }
    
    private static int verifyDiagonals(int[][] symbols){
        int xqtt = 0, oqtt = 0;
        for (int i=0;i<symbols.length;i++){
            if (symbols[i][i]==1)oqtt++;
            else if (symbols[i][i]==2)xqtt++;
        }if (oqtt==3)return 2;
        if (xqtt==3)return 1;
        
        xqtt = 0; 
        oqtt = 0;
        for (int i=0;i<symbols.length;i++){
            if (symbols[i][symbols.length-i-1]==1)oqtt++;
            else if (symbols[i][symbols.length-i-1]==2)xqtt++;
        }if (oqtt==3)return 2;
        if (xqtt==3)return 1;
        
        return 0;
    }
    
    private static boolean hasFinished(int[][] symbols){
        for (int i=0;i<symbols.length;i++){
            for (int j=0;j<symbols.length;j++){
                if (symbols[j][i]==0)return false;
            }
        }
        return true;
    }
    
    public static int getGameState(int[][] symbols){
        int win = AI.verifyCollums(symbols)|AI.verifyDiagonals(symbols)|AI.verifyRows(symbols);
        if (win==0&&!hasFinished(symbols))win = -2;
        if (win==2)win=-1;
        
        return win;
    }
    
    private static int alphabeta(int[][] symbols,int alpha,int beta,int player,boolean first){
        int idx = 0, v = 0, aux, besti = 0,bestj = 0, nextplayer = player%2+1;
        
        int stateVal = getGameState(symbols);
        
        if (stateVal!=-2){
            return stateVal;
        }
        
        if (player==2){
            v = -10000;
            for (int i=0;i<symbols.length;i++){
                for (int j=0;j<symbols.length;j++){
                    if (symbols[i][j]==0){
                        symbols[i][j] = player;
                        aux = alphabeta(symbols,alpha,beta,nextplayer,false);
                        if (v<aux){
                            v = aux; besti = i; bestj = j;
                        }
                        symbols[i][j] = 0;
                        alpha = Math.max(alpha,v);
                        if (beta<=alpha)break;
                    }
                }
            }
        }else{
            v = 10000;
            for (int i=0;i<symbols.length;i++){
                    for (int j=0;j<symbols.length;j++){
                        if (symbols[i][j]==0){
                        symbols[i][j] = player;
                        v = Math.min(alphabeta(symbols,alpha,beta,nextplayer,false),v);
                        symbols[i][j] = 0;
                        beta = Math.min(beta,v);
                        if (beta<=alpha)break;
                    }
                }
            }
        }
        
        if (first)symbols[besti][bestj]=2;
        return v;
    }
    
    public static void makeMove(int[][] symbols){
        alphabeta(symbols,-1000,1000,2,true);
    }
}
