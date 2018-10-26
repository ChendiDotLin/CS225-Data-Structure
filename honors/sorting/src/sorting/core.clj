 sorting.core
  (:gen-class))

(defn cas
    "Compare elements `i` and `j` of array `arr`, swapping them if they are out of order.
      Returns the new array." 
    [arr [i j]]
    (if (< (arr j) (arr i))
          (assoc arr i (arr j)
                            j (arr i))
          arr))

(defn multi-cas
    "Takes an array a vector of swapping pairs and perform all the swaps needed."
    [arr swaps]
    (reduce cas arr (partition 2 swaps)))

(def n6 [[0 1 2 3 4 5] [0 2 3 5] [1 4] [0 1 2 3 4 5] [1 2 3 4] [2 3]])

(defn n-sort
    [arr sv]
    (reduce multi-cas arr sv))

(defn add-bit
    [v]
    [(conj v 0) (conj v 1)])

(defn zero-one
    [n]
    (if (= n 0)
          [[]]
          (mapcat add-bit (zero-one (- n 1)))))

(defn num-ele
    [nw]
    (+ 1 (apply max (map #(apply max %) nw))))

(defn verify
    [nw]
    (every? (fn [v] (apply <= v)) (map n-sort (zero-one (num-ele nw)) (repeat nw))))

(defn bubble-help
    "helper function for bubble-sort1 and bubble-sort3"
    [n]
    (if (= n 2)
          [[0 1]]
          (conj (bubble-help (- n 1)) (mapv inc (last (bubble-help (- n 1)))))))

(defn bubble-help2
    "another helper function for bubble-sort1 and bubble-sort3, it does the same thing as bubble-help does. Just for fun!"
    [n]
    (vec (map vec (partition 2 1 (range n)))))

(defn bubble-sort
    "inspired by bubble-help2. bubble sort soluiton with NO helper function. Well, this actually uses bubble-help2 in some sense"
    [n]
    (vec (map vec (mapcat (fn [n] (partition 2 1 (range n))) (range n 1 -1)))))

(defn bubble-sort1
    "bubble sort solution 2 with ONE helper function (- . -)"
    [n]
    (if (= n 2)
          [[0 1]]
          (vec (concat (bubble-help n) (bubble-sort1 (- n 1))))))

(defn bubble-sort2
    "bubble sort solution 3 with no helper function :)"
    [n]
    (if (= n 2)
          [[0 1]]
          (vec (concat [[0 1]] (map (fn [v] (mapv inc v)) (take (- n 2) (bubble-sort2 (- n 1)))) (bubble-sort2 (- n 1))))))

(defn bubble-sort3
    "bubble sort solution 4 with the same helper function in bubble-sort1, but no recurrsion"
    [n]
    (vec (mapcat bubble-help (range n 1 -1))))

(defn bubble-single 
      [num]
      [(- num 1) num]
     )

(defn bubble-step
      [n arr counter]
      (if (= counter n) arr
                      (bubble-step n (conj arr (bubble-single counter)) (+ counter 1))))

(defn bubble-sort-in
      [n arr]
      (if (< n 2) arr
                    (bubble-sort-in (- n 1) (bubble-step n arr 1))))

(defn bubble-sort4
    "bubble sort solution 5 with 3 helper function"
      [n]
      (def arr [])
      (bubble-sort-in n arr))

(defn have-same-element
      [a b]
      (cond (empty? a) nil
                              (= -1 (.indexOf b (first a))) (have-same-element (rest a) b)
                             :otherwise (.indexOf b (first a))))

(defn qualified
      [network n counter]
      (cond (= counter (count network)) nil
                              (and (nil? (have-same-element (network n) (network counter))) 
                                                                       (nil? (have-same-element (network counter) (network (- counter 1))))) counter
                              :otherwise (qualified network n (+ counter 1))))

(defn concave-and-drop
      [network a b]
      (into [] (concat (subvec (assoc network a (into [] (concat (network b) (network a)))) 0 b) (subvec (assoc network a (into [] (concat (network b) (network a)))) (+ b 1) (count network)))) 
    )

(defn collapse-helper
      [network n]
      (cond (= (count network) n) network
                              (nil? (qualified network n (+ n 1))) (collapse-helper network (+ n 1))
                              :otherwise (collapse-helper (concave-and-drop network n (qualified network n (+ n 1))) n)))
                
(defn collapse
      [network]
      (collapse-helper network 0))
