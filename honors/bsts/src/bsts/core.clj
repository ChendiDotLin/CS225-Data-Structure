(ns bsts.core)



(defrecord Node [left key value right])

(defn add 
  "Adds key `k` and value `v` to tree `bst`."
  [bst k v]
  (cond (nil? bst) (Node. nil k v nil)
        (> 0 (compare k (:key bst))) (Node. (add (:left bst) k v)
                                   (:key bst)
                                   (:value bst)
                                   (:right bst))
        :else  (Node. (:left bst)
                      (:key bst)
                      (:value bst)
                      (add (:right bst) k v)) ) )

(defn make-tree
  "We may want to change the representation of this later."
  []
  nil)

(defn show [bst]
  (cond (nil? bst) " x "
        (and (nil? (:left bst))
             (nil? (:right bst)))  (str " " (:key bst) "/" (:value bst) " ")
        :otherwise (str "(" (:key bst) "/" (:value bst) " " (show (:left bst)) " " 
                        (show (:right bst)) ")"))) 

(defn find [bst desire]
  (cond (nil? bst) nil
        (= desire (:key bst)) (:value bst)
        (> 0 (compare desire (:key bst))) (find (:left bst) desire)
        :else (find (:right bst) desire) ))


(defn size
  "Return the number of nodes in a BST."
  [bst]
  (if (nil? bst) 0
	 (+ 1  (size (:left bst)) (size (:right bst))))
)
(defn findiop
  "find iop"
  [root]
  (if (nil? (:right root)) root
        (findiop (:right root)))
)


(defn delete 
  "Deletes the node with `victim` as its key."
  [bst victim]
	(cond (nil? bst) nil
		(and (nil? (:left bst)) 
			(nil? (:right bst))
			 (= victim (:key bst))) nil
		(and (nil? (:left bst))
			(= victim (:key bst))) (Node. (delete (:left (:right bst)) victim)
							(:key (:right bst))
							(:value (:right bst))
							(delete (:right (:right bst)) victim))
		
		(and (nil? (:right bst))
			(= victim (:key bst))) (Node. (delete (:left (:left bst)) victim)
                                                        (:key (:left bst))
                                                        (:value (:left bst))
                                                        (delete (:right (:left bst)) victim))  
		(= victim (:key bst)) (Node. (delete (:left bst) (:key (findiop (:left bst))))
							(:key (findiop (:left bst)))
							(:value (findiop (:left bst)))
							(delete (:right bst) victim))
		:otherwise (Node. (delete (:left bst) victim)
				(:key bst)
				(:value bst)
				(delete (:right bst) victim))
)
)                                     
