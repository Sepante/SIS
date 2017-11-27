import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

#n = 243
#n = nrange[nindex]
norm_data = data / nrange[nindex]

opacity_num =  100/runNum
cmap = mpl.cm.rainbow
for qindex in range(q_size):
    q=qrange[qindex]
    for pindex in range(p_size):
        current_data = norm_data[pindex, qindex, :]
            
        high_a = current_data[:, 1] > 0.02
        high_b = current_data[:, 2] > 0.02
        joint_condition = np.logical_and(high_a, high_b)
        joint_cluster = current_data[joint_condition,0]
    
        plt.plot([prange[pindex]], [joint_cluster],'o' , color='r', alpha=opacity_num )
        
        single_cluster = current_data[ np.logical_not(joint_condition) , 0]
        plt.plot([prange[pindex]], [single_cluster],'o' , color='b', alpha=opacity_num )
        #data_type = " $Primary$ $School: $"
        dis_type = dis_type.replace('\n','')
        data_type = data_type.replace('\n','')
        #name_string = data_type +"$Phase: $"+" $n=$"+str(n)+ ", $q=$" + str(qrange[qindex]) + ", $r=$" + str(rrange[0])
        name_string = dis_type + ", " + data_type +", $Phase$: $n=$"+str(n)+ ", $q=$" + str(qrange[qindex]) + ", $r=$" + str(rrange[0])
        plt.suptitle(name_string)
        plt.xlabel('$p$')   
        plt.ylabel('$R$')
        #plt.xlim([0.03,0.1])
        plt.ylim([0-0.02,1+0.02])
        #plt.ylim([0.2, 1])
        #plt.ylim([0.8,1+0.02])*=
        name_string = name_string.replace('$','')
        
        
        location = "results/"
    plt.savefig(location+name_string+".png")
    plt.show()