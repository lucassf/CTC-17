package main;

import javax.swing.JButton;

public class MainFrame extends javax.swing.JFrame {
    
    private int[][] symbols;
    private GameState gameState;
    private JButton[][] buttons;
    private final int GRID_SIZE = 3;
    
    public MainFrame() {
        symbols = new int[GRID_SIZE][];
        for (int i=0;i<symbols.length;i++)symbols[i] = new int[3];
        buttons = new JButton[GRID_SIZE][];
        for (int i=0;i<buttons.length;i++){
            buttons[i] = new JButton[3];
            for (int j=0;j<buttons.length;j++)buttons[i][j] = new JButton();
        }
        gameState = GameState.IDDLE;
        
        initComponents();
    }
    
    private void verifyGameState(){
        if (gameState!=GameState.EXECUTION)return;
        
        int win = AI.getGameState(symbols);
        if (win==-1)gameState = GameState.WIN;
        else if (win==1)gameState = GameState.LOSE;
        else if (win==0)gameState = GameState.DRAW;
    }
    
    private void makeMove(int x,int y){
        if (gameState != GameState.EXECUTION || symbols[x][y]!=0)return;
        
        symbols[x][y] = 1;
        AI.makeMove(symbols);
        verifyGameState();
        
        updateFrame();
    }
    
    private void updateFrame(){
        for (int i=0;i<symbols.length;i++){
            for (int j=0;j<symbols.length;j++){
                if (symbols[i][j]==0)buttons[i][j].setText("");
                else if (symbols[i][j]==1)buttons[i][j].setText("O");
                else if (symbols[i][j]==2)buttons[i][j].setText("X");
            }
        }
        if (gameState==GameState.DRAW)resultLabel.setText("Empate!");
        else if (gameState==GameState.WIN)resultLabel.setText("Venceu!");
        else if (gameState==GameState.LOSE)resultLabel.setText("Perdeu!");
        else resultLabel.setText("");
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        Button01 = buttons[0][1];
        Button02 = buttons[0][2];
        Button10 = buttons[1][0];
        Button11 = buttons[1][1];
        Button00 = buttons[0][0];
        Button12 = buttons[1][2];
        Button20 = buttons[2][0];
        Button21 = buttons[2][1];
        Button22 = buttons[2][2];
        newGameButton = new javax.swing.JButton();
        resultLabel = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        Button01.setEnabled(false);
        Button01.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button01ActionPerformed(evt);
            }
        });

        Button02.setEnabled(false);
        Button02.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button02ActionPerformed(evt);
            }
        });

        Button10.setEnabled(false);
        Button10.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button10ActionPerformed(evt);
            }
        });

        Button11.setEnabled(false);
        Button11.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button11ActionPerformed(evt);
            }
        });

        Button00.setEnabled(false);
        Button00.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button00ActionPerformed(evt);
            }
        });

        Button12.setEnabled(false);
        Button12.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button12ActionPerformed(evt);
            }
        });

        Button20.setEnabled(false);
        Button20.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button20ActionPerformed(evt);
            }
        });

        Button21.setEnabled(false);
        Button21.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button21ActionPerformed(evt);
            }
        });

        Button22.setEnabled(false);
        Button22.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Button22ActionPerformed(evt);
            }
        });

        newGameButton.setText("Novo jogo");
        newGameButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                newGameButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Button20, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(Button21, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Button10, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(Button11, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Button00, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(Button01, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(Button22, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Button12, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(resultLabel))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Button02, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(newGameButton)))
                .addContainerGap(70, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(Button01, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(Button02, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(Button00, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(newGameButton))
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(Button10, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(Button11, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(Button12, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(26, 26, 26)
                        .addComponent(resultLabel)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(Button20, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(Button21, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(Button22, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void newGameButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_newGameButtonActionPerformed
        gameState = GameState.EXECUTION;
        for (int i=0;i<symbols.length;i++){
            for (int j=0;j<symbols[i].length;j++){
                symbols[i][j] = 0;
                buttons[i][j].setEnabled(true);
            }
        }
        updateFrame();
    }//GEN-LAST:event_newGameButtonActionPerformed

    private void Button00ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button00ActionPerformed
        makeMove(0,0);
    }//GEN-LAST:event_Button00ActionPerformed

    private void Button01ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button01ActionPerformed
        makeMove(0,1);
    }//GEN-LAST:event_Button01ActionPerformed

    private void Button02ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button02ActionPerformed
        makeMove(0,2);
    }//GEN-LAST:event_Button02ActionPerformed

    private void Button10ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button10ActionPerformed
        makeMove(1,0);
    }//GEN-LAST:event_Button10ActionPerformed

    private void Button11ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button11ActionPerformed
        makeMove(1,1);
    }//GEN-LAST:event_Button11ActionPerformed

    private void Button12ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button12ActionPerformed
        makeMove(1,2);
    }//GEN-LAST:event_Button12ActionPerformed

    private void Button20ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button20ActionPerformed
        makeMove(2,0);
    }//GEN-LAST:event_Button20ActionPerformed

    private void Button21ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button21ActionPerformed
        makeMove(2,1);
    }//GEN-LAST:event_Button21ActionPerformed

    private void Button22ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Button22ActionPerformed
        makeMove(2,2);
    }//GEN-LAST:event_Button22ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainFrame().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton Button00;
    private javax.swing.JButton Button01;
    private javax.swing.JButton Button02;
    private javax.swing.JButton Button10;
    private javax.swing.JButton Button11;
    private javax.swing.JButton Button12;
    private javax.swing.JButton Button20;
    private javax.swing.JButton Button21;
    private javax.swing.JButton Button22;
    private javax.swing.JButton newGameButton;
    private javax.swing.JLabel resultLabel;
    // End of variables declaration//GEN-END:variables
}
