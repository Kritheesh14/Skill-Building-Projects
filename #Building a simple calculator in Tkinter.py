#Building a simple calculator in Tkinter


from tkinter import *


def inp(number):
    current = e.get()
    e.delete(0, END)
    e.insert(0, str(current) + str(number))

def clear():
    e.delete(0,END)

def result():
    try:    
        result=str(eval(e.get()))
        e.delete(0, END)
        e.insert(0, result)
    except:
        e.delete(0, END)
        e.insert(0, "Error")

root=Tk()
root.title('Calculator')
root.configure(bg='Black')

e= Entry(root,width=50,borderwidth='10',fg='orange',bg='black',font=('Times New Roman',8,'bold'))
e.grid(row=0,column=0,columnspan=3,padx=10,pady=10)




b1=Button(root,text='1',padx=40,pady=20,command=lambda: inp(1),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b1.grid(row=1,column=0)
b2=Button(root,text='2',padx=40,pady=20,command=lambda: inp(2),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b2.grid(row=1,column=1)
b3=Button(root,text='3',padx=40,pady=20,command=lambda: inp(3),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b3.grid(row=1,column=2)
b4=Button(root,text='4',padx=40,pady=20,command=lambda: inp(4),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b4.grid(row=2,column=0)
b5=Button(root,text='5',padx=40,pady=20,command=lambda: inp(5),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b5.grid(row=2,column=1)
b6=Button(root,text='6',padx=40,pady=20,command=lambda: inp(6),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b6.grid(row=2,column=2)
b7=Button(root,text='7',padx=40,pady=20,command=lambda: inp(7),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b7.grid(row=3,column=0)
b8=Button(root,text='8',padx=40,pady=20,command=lambda: inp(8),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b8.grid(row=3,column=1)
b9=Button(root,text='9',padx=40,pady=20,command=lambda: inp(9),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b9.grid(row=3,column=2)
b0=Button(root,text='0',padx=40,pady=20,command=lambda: inp(0),fg='orange',bg='black',font=('Times New Roman',16,'bold'))
b0.grid(row=4,column=0)


badd=Button(root,text='(+)',padx=40,pady=20,command=lambda: inp('+'),fg='orange',bg='black',font=('Times New Roman',16,'bold')).grid(row=4,column=1)
bsub=Button(root,text='(-)',padx=40,pady=20,command=lambda: inp('-'),fg='orange',bg='black',font=('Times New Roman',16,'bold')).grid(row=4,column=2)
bmul=Button(root,text='(x)',padx=40,pady=20,command=lambda: inp('*'),fg='orange',bg='black',font=('Times New Roman',16,'bold')).grid(row=5,column=1)
bdiv=Button(root,text='(÷)',padx=40,pady=20,command=lambda: inp('/'),fg='orange',bg='black',font=('Times New Roman',16,'bold')).grid(row=5,column=2)
beq=Button(root,text='(=)',padx=40,pady=20,command=result,fg='orange',bg='black',font=('Times New Roman',16,'bold')).grid(row=5,column=0)
bcl=Button(root,text='Clear',padx=120,pady=20,command=clear,fg='orange',bg='black',font=('Times New Roman',16,'bold')).grid(row=6,column=0,columnspan=3)


root.mainloop()