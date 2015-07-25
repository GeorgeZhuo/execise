import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.text.NumberFormat;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class ImageViewerFrame extends JFrame{
	
    private String filename;
    private JLabel label;
    private JLabel textLable;
    private JPanel panel;
    private JFileChooser chooser;
    private static final int DEFAULT_WIDTH = 500;
    private static final int DEFAULT_HEIGHT = 400;

    public ImageViewerFrame(){

        setTitle("ImageViewer");
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	panel = new JPanel(new FlowLayout());
        label = new JLabel();
	textLable = new JLabel();
        add(panel);
	panel.add(label);
	panel.add(textLable);
        chooser = new JFileChooser();
        chooser.setCurrentDirectory(new File("."));
        JMenuBar menubar = new JMenuBar();
        setJMenuBar(menubar);
        JMenu menu = new JMenu("File");
        menubar.add(menu);
        JButton binaryMenu = new JButton("Binaryzation");
        menubar.add(binaryMenu);
        JButton addNoice = new JButton("AddNoice");
        menubar.add(addNoice);
	JButton denoice = new JButton("Denoice");
	menubar.add(denoice);
	JButton result = new JButton("result");
	menubar.add(result);

        JMenuItem openItem = new JMenuItem("Open");
        menu.add(openItem);
        JMenuItem exitItem = new JMenuItem("Close");
        menu.add(exitItem);
        
        openItem.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
		    int result = chooser.showOpenDialog(null);
		    if(result == JFileChooser.APPROVE_OPTION){
			String name = chooser.getSelectedFile().getPath();
			filename = name;
			label.setIcon(new ImageIcon(name));
		    }
		}
	    });
        exitItem.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
		    System.exit(0);
		}
	    });
        
        binaryMenu.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
		    ImageDemo demo = new ImageDemo();
		    try {
			
			label.setIcon(new ImageIcon(demo.binaryzation(filename)));
			textLable.setText("Binaryzationing the image ");
		    } catch (IOException e) {

			e.printStackTrace();
		    }
		}
	    });
        addNoice.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
		    ImageDemo demo = new ImageDemo();
		    try {
            		label.setIcon(new ImageIcon(demo.addNoice("binaryzation.png")));
			textLable.setText("Adding 10% noice to the image");
		    } catch (IOException e) {

			e.printStackTrace();
		}
		    }
	    });
	denoice.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
		    ImageDemo demo = new ImageDemo();
		    try {
			label.setIcon(new ImageIcon(demo.denoice("addNoice.png")));
			textLable.setText("Denoice, click the result to get the recovering ratio ");
		    } catch (IOException e) {

			e.printStackTrace();
		    }
		}
	    });
	result.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent arg0) {
		    ImageDemo demo = new ImageDemo();
		    try {
			
			double percent = demo.result("binaryzation.png", "denoice.png");
			textLable.setText("Recovering ratio of the image is %" 
					  + String.format("%.4f", percent * 100.0));
		    } catch (IOException e) {

			e.printStackTrace();
		    }
		}
	    });  
    }
}
