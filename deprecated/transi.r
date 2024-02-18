library(igraph)
require(data.table)
setwd("C:/Users/tomys/Downloads/")
data<-read.table("./wikispeedia_paths-and-graph/paths_finished.tsv")

from=vector()
to=vector()
paths = as.character(data$V4)
arr<-as.list(strsplit(paths, ";"))
#start.time <- Sys.time()
max=length(arr)

for (h in 1:max){
  from_c=vector()
  to_c=vector()
  count = 0
  len = length(arr[[h]])
  if (len>1){
    for (j in 2:len){
      i=j-count
      if (arr[[h]][i]!="<"){
        from_c=append(from_c,arr[[h]][i-1]) #Le premier element ne peut pas etre un retour en arriere
        to_c=append(to_c,arr[[h]][i])
      }
      else{
        arr[[h]]=arr[[h]][-c(i,i-1)]
        count = count+2
      }
    }
    from = append(from,from_c)
    to = append(to,to_c)
  }
  #for (i in 1:length(to)){
  #  message(sprintf("From : %s | To : %s",from[[i]],to[[i]]))
  #}
}

graph=graph_from_edgelist(cbind(from,to))
(matrixAdj=as_adjacency_matrix(graph))

genTransition <- function(matrixAdj){
  trans <- t(matrixAdj)
  for(i in c(1:(nrow(trans)))){
    s <- sum(trans[,i])
    if(s!=0){
      trans[,i] = trans[,i]/s
    }
  return(trans)
  }
}

matrixTransi=genTransition(as.matrix(matrixAdj))

write.table(matrixTransi, file="transi.txt", row.names=TRUE, col.names=TRUE)

#write.table(from, file="from.txt", row.names=FALSE, col.names=FALSE)
#write.table(to, file="to.txt", row.names=FALSE, col.names=FALSE)


#end.time <- Sys.time()
#time.taken <- end.time - start.time
#print(time.taken)